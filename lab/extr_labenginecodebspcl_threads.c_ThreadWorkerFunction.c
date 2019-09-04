#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int GetThreadWork () ; 
 int /*<<< orphan*/  workfunction (int) ; 

void ThreadWorkerFunction(int threadnum)
{
	int		work;

	while(1)
	{
		work = GetThreadWork ();
		if (work == -1)
			break;
//printf ("thread %i, work %i\n", threadnum, work);
		workfunction(work);
	} //end while
}