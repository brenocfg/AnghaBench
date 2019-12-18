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
typedef  scalar_t__ s_char ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  TRUE ; 
 double measured_tick ; 
 int /*<<< orphan*/  msyslog (int /*<<< orphan*/ ,char*,double,...) ; 
 scalar_t__ sys_precision ; 
 double sys_tick ; 
 int /*<<< orphan*/  trunc_os_clock ; 

void
set_sys_tick_precision(
	double tick
	)
{
	int i;

	if (tick > 1.) {
		msyslog(LOG_ERR,
			"unsupported tick %.3f > 1s ignored", tick);
		return;
	}
	if (tick < measured_tick) {
		msyslog(LOG_ERR,
			"proto: tick %.3f less than measured tick %.3f, ignored",
			tick, measured_tick);
		return;
	} else if (tick > measured_tick) {
		trunc_os_clock = TRUE;
		msyslog(LOG_NOTICE,
			"proto: truncating system clock to multiples of %.9f",
			tick);
	}
	sys_tick = tick;

	/*
	 * Find the nearest power of two.
	 */
	for (i = 0; tick <= 1; i--)
		tick *= 2;
	if (tick - 1 > 1 - tick / 2)
		i++;

	sys_precision = (s_char)i;
}