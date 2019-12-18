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
typedef  scalar_t__ u_int ;

/* Variables and functions */
 scalar_t__ MON_OFF ; 
 scalar_t__ mon_enabled ; 
 int /*<<< orphan*/  mon_start (scalar_t__) ; 
 int /*<<< orphan*/  mon_stop (scalar_t__) ; 
 int /*<<< orphan*/  win_time_stepped () ; 

void
ntpd_time_stepped(void)
{
	u_int saved_mon_enabled;

	/*
	 * flush the monitor MRU list which contains l_fp timestamps
	 * which should not be compared across the step.
	 */
	if (MON_OFF != mon_enabled) {
		saved_mon_enabled = mon_enabled;
		mon_stop(MON_OFF);
		mon_start(saved_mon_enabled);
	}

	/* inform interpolating Windows code to allow time to go back */
#ifdef SYS_WINNT
	win_time_stepped();
#endif
}