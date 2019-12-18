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
 int ppc_tb_freq ; 
 int watchdog_thresh ; 
 int wd_panic_timeout_tb ; 
 int wd_smp_panic_timeout_tb ; 
 int wd_timer_period_ms ; 

__attribute__((used)) static void watchdog_calc_timeouts(void)
{
	wd_panic_timeout_tb = watchdog_thresh * ppc_tb_freq;

	/* Have the SMP detector trigger a bit later */
	wd_smp_panic_timeout_tb = wd_panic_timeout_tb * 3 / 2;

	/* 2/5 is the factor that the perf based detector uses */
	wd_timer_period_ms = watchdog_thresh * 1000 * 2 / 5;
}