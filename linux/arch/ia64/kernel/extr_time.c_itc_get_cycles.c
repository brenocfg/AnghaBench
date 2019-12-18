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
typedef  unsigned long u64 ;
struct clocksource {int dummy; } ;
struct TYPE_2__ {unsigned long itc_lastcycle; int /*<<< orphan*/  itc_jitter; } ;

/* Variables and functions */
 unsigned long cmpxchg (unsigned long*,unsigned long,unsigned long) ; 
 unsigned long get_cycles () ; 
 TYPE_1__ itc_jitter_data ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static u64 itc_get_cycles(struct clocksource *cs)
{
	unsigned long lcycle, now, ret;

	if (!itc_jitter_data.itc_jitter)
		return get_cycles();

	lcycle = itc_jitter_data.itc_lastcycle;
	now = get_cycles();
	if (lcycle && time_after(lcycle, now))
		return lcycle;

	/*
	 * Keep track of the last timer value returned.
	 * In an SMP environment, you could lose out in contention of
	 * cmpxchg. If so, your cmpxchg returns new value which the
	 * winner of contention updated to. Use the new value instead.
	 */
	ret = cmpxchg(&itc_jitter_data.itc_lastcycle, lcycle, now);
	if (unlikely(ret != lcycle))
		return ret;

	return now;
}