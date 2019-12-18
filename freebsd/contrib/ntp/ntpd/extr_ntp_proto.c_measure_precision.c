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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  measure_tick_fuzz () ; 
 int /*<<< orphan*/  measured_tick ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  set_sys_fuzz (int) ; 
 int /*<<< orphan*/  set_sys_tick_precision (int /*<<< orphan*/ ) ; 
 int sys_fuzz ; 
 int /*<<< orphan*/  sys_precision ; 
 int sys_tick ; 
 int /*<<< orphan*/  trunc_os_clock ; 

void
measure_precision(void)
{
	/*
	 * With sys_fuzz set to zero, get_systime() fuzzing of low bits
	 * is effectively disabled.  trunc_os_clock is FALSE to disable
	 * get_ostime() simulation of a low-precision system clock.
	 */
	set_sys_fuzz(0.);
	trunc_os_clock = FALSE;
	measured_tick = measure_tick_fuzz();
	set_sys_tick_precision(measured_tick);
	msyslog(LOG_INFO, "proto: precision = %.3f usec (%d)",
		sys_tick * 1e6, sys_precision);
	if (sys_fuzz < sys_tick) {
		msyslog(LOG_NOTICE, "proto: fuzz beneath %.3f usec",
			sys_fuzz * 1e6);
	}
}