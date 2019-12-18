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
typedef  int u64 ;
struct clocksource {int dummy; } ;

/* Variables and functions */
 int TIMER_MULTIPLIER ; 
 scalar_t__ TT_MODE_OFF ; 
 int os_nsecs () ; 
 scalar_t__ time_travel_mode ; 
 int /*<<< orphan*/  time_travel_set_time (int) ; 
 int time_travel_time ; 

__attribute__((used)) static u64 timer_read(struct clocksource *cs)
{
	if (time_travel_mode != TT_MODE_OFF) {
		/*
		 * We make reading the timer cost a bit so that we don't get
		 * stuck in loops that expect time to move more than the
		 * exact requested sleep amount, e.g. python's socket server,
		 * see https://bugs.python.org/issue37026.
		 */
		time_travel_set_time(time_travel_time + TIMER_MULTIPLIER);
		return time_travel_time / TIMER_MULTIPLIER;
	}

	return os_nsecs() / TIMER_MULTIPLIER;
}