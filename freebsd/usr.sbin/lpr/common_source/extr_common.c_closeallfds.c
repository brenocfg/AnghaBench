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
 scalar_t__ USE_CLOSEFROM ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  closefrom (int) ; 
 int getdtablesize () ; 

void
closeallfds(int start)
{
	int stop;

	if (USE_CLOSEFROM)		/* The faster, modern solution */
		closefrom(start);
	else {
		/* This older logic can be pretty awful on some OS's.  The
		 * getdtablesize() might return ``infinity'', and then this
		 * will waste a lot of time closing file descriptors which
		 * had never been open()-ed. */
		stop = getdtablesize();
		for (; start < stop; start++)
			close(start);
	}
}