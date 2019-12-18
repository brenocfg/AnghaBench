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
 int /*<<< orphan*/  SCHED_AFFINITY_DEFAULT ; 
 int SCHED_SLICE_DEFAULT_DIVISOR ; 
 int SCHED_SLICE_MIN_DIVISOR ; 
 int SCHED_TICK_SHIFT ; 
 int /*<<< orphan*/  affinity ; 
 int balance_interval ; 
 int balance_ticks ; 
 int /*<<< orphan*/  hogticks ; 
 int hz ; 
 int /*<<< orphan*/  imax (int,int) ; 
 int max (int,int) ; 
 int realstathz ; 
 int sched_idlespinthresh ; 
 int sched_slice ; 
 int sched_slice_min ; 
 int stathz ; 
 int tickincr ; 

__attribute__((used)) static void
sched_initticks(void *dummy)
{
	int incr;

	realstathz = stathz ? stathz : hz;
	sched_slice = realstathz / SCHED_SLICE_DEFAULT_DIVISOR;
	sched_slice_min = sched_slice / SCHED_SLICE_MIN_DIVISOR;
	hogticks = imax(1, (2 * hz * sched_slice + realstathz / 2) /
	    realstathz);

	/*
	 * tickincr is shifted out by 10 to avoid rounding errors due to
	 * hz not being evenly divisible by stathz on all platforms.
	 */
	incr = (hz << SCHED_TICK_SHIFT) / realstathz;
	/*
	 * This does not work for values of stathz that are more than
	 * 1 << SCHED_TICK_SHIFT * hz.  In practice this does not happen.
	 */
	if (incr == 0)
		incr = 1;
	tickincr = incr;
#ifdef SMP
	/*
	 * Set the default balance interval now that we know
	 * what realstathz is.
	 */
	balance_interval = realstathz;
	balance_ticks = balance_interval;
	affinity = SCHED_AFFINITY_DEFAULT;
#endif
	if (sched_idlespinthresh < 0)
		sched_idlespinthresh = 2 * max(10000, 6 * hz) / realstathz;
}