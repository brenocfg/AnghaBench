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
 scalar_t__ TT_MODE_BASIC ; 
 scalar_t__ TT_MODE_INFCPU ; 
 scalar_t__ TT_TMR_DISABLED ; 
 scalar_t__ TT_TMR_ONESHOT ; 
 scalar_t__ TT_TMR_PERIODIC ; 
 int /*<<< orphan*/  deliver_alarm () ; 
 int /*<<< orphan*/  os_timer_disable () ; 
 int /*<<< orphan*/  os_timer_one_shot (unsigned long long) ; 
 int /*<<< orphan*/  os_timer_set_interval (scalar_t__) ; 
 scalar_t__ time_travel_mode ; 
 int /*<<< orphan*/  time_travel_set_time (unsigned long long) ; 
 int /*<<< orphan*/  time_travel_set_timer_expiry (scalar_t__) ; 
 int /*<<< orphan*/  time_travel_set_timer_mode (scalar_t__) ; 
 unsigned long long time_travel_time ; 
 unsigned long long time_travel_timer_expiry ; 
 scalar_t__ time_travel_timer_interval ; 
 scalar_t__ time_travel_timer_mode ; 

__attribute__((used)) static void time_travel_sleep(unsigned long long duration)
{
	unsigned long long next = time_travel_time + duration;

	if (time_travel_mode != TT_MODE_INFCPU)
		os_timer_disable();

	while (time_travel_timer_mode == TT_TMR_PERIODIC &&
	       time_travel_timer_expiry < time_travel_time)
		time_travel_set_timer_expiry(time_travel_timer_expiry +
					     time_travel_timer_interval);

	if (time_travel_timer_mode != TT_TMR_DISABLED &&
	    time_travel_timer_expiry < next) {
		if (time_travel_timer_mode == TT_TMR_ONESHOT)
			time_travel_set_timer_mode(TT_TMR_DISABLED);
		/*
		 * In basic mode, time_travel_time will be adjusted in
		 * the timer IRQ handler so it works even when the signal
		 * comes from the OS timer, see there.
		 */
		if (time_travel_mode != TT_MODE_BASIC)
			time_travel_set_time(time_travel_timer_expiry);

		deliver_alarm();
	} else {
		time_travel_set_time(next);
	}

	if (time_travel_mode != TT_MODE_INFCPU) {
		if (time_travel_timer_mode == TT_TMR_PERIODIC)
			os_timer_set_interval(time_travel_timer_interval);
		else if (time_travel_timer_mode == TT_TMR_ONESHOT)
			os_timer_one_shot(time_travel_timer_expiry - next);
	}
}