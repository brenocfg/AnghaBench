#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int tc_frequency; } ;
struct TYPE_3__ {TYPE_2__ tc; } ;

/* Variables and functions */
 int /*<<< orphan*/  TSENTER () ; 
 int /*<<< orphan*/  TSEXIT () ; 
 int aml8726_get_timecount (TYPE_2__*) ; 
 TYPE_1__* aml8726_timer_sc ; 
 int /*<<< orphan*/  cpufunc_nullop () ; 

void
DELAY(int usec)
{
	uint32_t counter;
	uint32_t delta, now, previous, remaining;

	/* Timer has not yet been initialized */
	if (aml8726_timer_sc == NULL) {
		for (; usec > 0; usec--)
			for (counter = 200; counter > 0; counter--) {
				/* Prevent gcc from optimizing out the loop */
				cpufunc_nullop();
			}
		return;
	}
	TSENTER();

	/*
	 * Some of the other timers in the source tree do this calculation as:
	 *
	 *   usec * ((sc->tc.tc_frequency / 1000000) + 1)
	 *
	 * which gives a fairly pessimistic result when tc_frequency is an exact
	 * multiple of 1000000.  Given the data type and typical values for
	 * tc_frequency adding 999999 shouldn't overflow.
	 */
	remaining = usec * ((aml8726_timer_sc->tc.tc_frequency + 999999) /
	    1000000);

	/*
	 * We add one since the first iteration may catch the counter just
	 * as it is changing.
	 */
	remaining += 1;

	previous = aml8726_get_timecount(&aml8726_timer_sc->tc);

	for ( ; ; ) {
		now = aml8726_get_timecount(&aml8726_timer_sc->tc);

		/*
		 * If the timer has rolled over, then we have the case:
		 *
		 *   if (previous > now) {
		 *     delta = (0 - previous) + now
		 *   }
		 *
		 * which is really no different then the normal case.
		 * Both cases are simply:
		 *
		 *   delta = now - previous.
		 */
		delta = now - previous;
		
		if (delta >= remaining)
			break;

		previous = now;
		remaining -= delta;
	}
	TSEXIT();
}