/* +---------------------------------------------------------------------------+
   |          The Mobile Robot Programming Toolkit (MRPT) C++ library          |
   |                                                                           |
   |                       http://www.mrpt.org/                                |
   |                                                                           |
   |   Copyright (C) 2005-2011  University of Malaga                           |
   |                                                                           |
   |    This software was written by the Machine Perception and Intelligent    |
   |      Robotics Lab, University of Malaga (Spain).                          |
   |    Contact: Jose-Luis Blanco  <jlblanco@ctima.uma.es>                     |
   |                                                                           |
   |  This file is part of the MRPT project.                                   |
   |                                                                           |
   |     MRPT is free software: you can redistribute it and/or modify          |
   |     it under the terms of the GNU General Public License as published by  |
   |     the Free Software Foundation, either version 3 of the License, or     |
   |     (at your option) any later version.                                   |
   |                                                                           |
   |   MRPT is distributed in the hope that it will be useful,                 |
   |     but WITHOUT ANY WARRANTY; without even the implied warranty of        |
   |     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
   |     GNU General Public License for more details.                          |
   |                                                                           |
   |     You should have received a copy of the GNU General Public License     |
   |     along with MRPT.  If not, see <http://www.gnu.org/licenses/>.         |
   |                                                                           |
   +---------------------------------------------------------------------------+ */

#include <mrpt/utils.h>
#include <mrpt/synch.h>

using namespace mrpt;
using namespace mrpt::synch;
using namespace mrpt::utils;
using namespace std;

CCriticalSection  csTest("csTest");

CStdOutStream	myOutStream;

// ------------------------------------------------------
//						MAIN
// ------------------------------------------------------
int main()
{
	try
	{
		csTest.m_debugOut = &myOutStream;

		cout << "Part 1: Normal usage, we'll lock, then unlock the critical section" << endl << endl;
		{
			synch::CCriticalSectionLocker  locker(&csTest);
			cout << "I possess the crit. section..." << endl;
		}

		cout << endl << "Part 2: Bad usage, we'll lock, then lock again the critical section" << endl << endl;
		{
			synch::CCriticalSectionLocker  locker(&csTest);
			csTest.enter();

			cout << "This message shouldn't appear, an exception raised before instead!!" << endl;
		}

		return 0;
	} catch (std::exception &e)
	{
		std::cout << "MRPT exception caught: " << e.what() << std::endl;
		return -1;
	}
	catch (...)
	{
		printf("Untyped exception!!");
		return -1;
	}
}
