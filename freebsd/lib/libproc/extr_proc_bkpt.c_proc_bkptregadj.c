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
 unsigned long BREAKPOINT_ADJUST_SZ ; 

void
proc_bkptregadj(unsigned long *pc)
{

	(void)pc;
#ifdef BREAKPOINT_ADJUST_SZ
	*pc = *pc - BREAKPOINT_ADJUST_SZ;
#endif
}