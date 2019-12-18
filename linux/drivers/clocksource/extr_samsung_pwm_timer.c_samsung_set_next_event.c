#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct clock_event_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  event_id; } ;

/* Variables and functions */
 TYPE_1__ pwm ; 
 int /*<<< orphan*/  samsung_time_setup (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  samsung_time_start (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int samsung_set_next_event(unsigned long cycles,
				struct clock_event_device *evt)
{
	/*
	 * This check is needed to account for internal rounding
	 * errors inside clockevents core, which might result in
	 * passing cycles = 0, which in turn would not generate any
	 * timer interrupt and hang the system.
	 *
	 * Another solution would be to set up the clockevent device
	 * with min_delta = 2, but this would unnecessarily increase
	 * the minimum sleep period.
	 */
	if (!cycles)
		cycles = 1;

	samsung_time_setup(pwm.event_id, cycles);
	samsung_time_start(pwm.event_id, false);

	return 0;
}