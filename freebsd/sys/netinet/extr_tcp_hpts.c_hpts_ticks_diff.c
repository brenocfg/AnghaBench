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
 int NUM_OF_HPTSI_SLOTS ; 

__attribute__((used)) static inline int
hpts_ticks_diff(int prev_tick, int tick_now)
{
	/*
	 * Given two ticks that are someplace
	 * on our wheel. How far are they apart?
	 */
	if (tick_now > prev_tick)
		return (tick_now - prev_tick);
	else if (tick_now == prev_tick)
		/* 
		 * Special case, same means we can go all of our 
		 * wheel less one slot.
		 */
		return (NUM_OF_HPTSI_SLOTS - 1);
	else
		return ((NUM_OF_HPTSI_SLOTS - prev_tick) + tick_now);
}