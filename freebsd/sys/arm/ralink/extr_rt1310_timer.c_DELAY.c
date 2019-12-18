#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {int tc_frequency; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 scalar_t__ rt1310_get_timecount (TYPE_1__*) ; 
 TYPE_1__ rt1310_timecounter ; 
 int /*<<< orphan*/  rt1310_timer_initialized ; 

void
DELAY(int usec)
{
	uint32_t counter;
	uint32_t first, last;
	int val = (rt1310_timecounter.tc_frequency / 1000000 + 1) * usec;

	/* Timer is not initialized yet */
	if (!rt1310_timer_initialized) {
		for (; usec > 0; usec--)
			for (counter = 100; counter > 0; counter--)
				;
		return;
	}
	TSENTER();

	first = rt1310_get_timecount(&rt1310_timecounter);
	while (val > 0) {
		last = rt1310_get_timecount(&rt1310_timecounter);
		if (last < first) {
			/* Timer rolled over */
			last = first;
		}
		
		val -= (last - first);
		first = last;
	}
	TSEXIT();
}