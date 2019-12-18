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
typedef  scalar_t__ uint32_t ;
struct tcp_hpts_entry {int p_hpts_active; scalar_t__ p_wheel_complete; scalar_t__ p_runningtick; scalar_t__ p_prev_slot; scalar_t__ p_cur_slot; scalar_t__ p_nxt_slot; } ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 scalar_t__ NUM_OF_HPTSI_SLOTS ; 
 int /*<<< orphan*/  combined_wheel_wrap ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 scalar_t__ hpts_ticks_diff (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int32_t
max_ticks_available(struct tcp_hpts_entry *hpts, uint32_t wheel_tick, uint32_t *target_tick)
{
	uint32_t dis_to_travel, end_tick, pacer_to_now, avail_on_wheel;

	if ((hpts->p_hpts_active == 1) &&
	    (hpts->p_wheel_complete == 0)) {
		end_tick = hpts->p_runningtick;
		/* Back up one tick */
		if (end_tick == 0)
			end_tick = NUM_OF_HPTSI_SLOTS - 1;
		else
			end_tick--;
		if (target_tick)
			*target_tick = end_tick;
	} else {
		/*
		 * For the case where we are
		 * not active, or we have
		 * completed the pass over
		 * the wheel, we can use the
		 * prev tick and subtract one from it. This puts us
		 * as far out as possible on the wheel.
		 */
		end_tick = hpts->p_prev_slot;
		if (end_tick == 0)
			end_tick = NUM_OF_HPTSI_SLOTS - 1;
		else
			end_tick--;
		if (target_tick)
			*target_tick = end_tick;
		/* 
		 * Now we have close to the full wheel left minus the 
		 * time it has been since the pacer went to sleep. Note
		 * that wheel_tick, passed in, should be the current time
		 * from the perspective of the caller, mapped to the wheel.
		 */
		if (hpts->p_prev_slot != wheel_tick)
			dis_to_travel = hpts_ticks_diff(hpts->p_prev_slot, wheel_tick);
		else
			dis_to_travel = 1;
		/* 
		 * dis_to_travel in this case is the space from when the 
		 * pacer stopped (p_prev_slot) and where our wheel_tick 
		 * is now. To know how many slots we can put it in we 
		 * subtract from the wheel size. We would not want
		 * to place something after p_prev_slot or it will
		 * get ran too soon.
		 */
		return (NUM_OF_HPTSI_SLOTS - dis_to_travel);
	}
	/* 
	 * So how many slots are open between p_runningtick -> p_cur_slot 
	 * that is what is currently un-available for insertion. Special
	 * case when we are at the last slot, this gets 1, so that
	 * the answer to how many slots are available is all but 1.
	 */
	if (hpts->p_runningtick == hpts->p_cur_slot)
		dis_to_travel = 1;
	else
		dis_to_travel = hpts_ticks_diff(hpts->p_runningtick, hpts->p_cur_slot);
	/* 
	 * How long has the pacer been running?
	 */
	if (hpts->p_cur_slot != wheel_tick) {
		/* The pacer is a bit late */
		pacer_to_now = hpts_ticks_diff(hpts->p_cur_slot, wheel_tick);
	} else {
		/* The pacer is right on time, now == pacers start time */
		pacer_to_now = 0;
	}
	/* 
	 * To get the number left we can insert into we simply
	 * subract the distance the pacer has to run from how
	 * many slots there are.
	 */
	avail_on_wheel = NUM_OF_HPTSI_SLOTS - dis_to_travel;
	/* 
	 * Now how many of those we will eat due to the pacer's 
	 * time (p_cur_slot) of start being behind the 
	 * real time (wheel_tick)?
	 */
	if (avail_on_wheel <= pacer_to_now) {
		/* 
		 * Wheel wrap, we can't fit on the wheel, that
		 * is unusual the system must be way overloaded!
		 * Insert into the assured tick, and return special
		 * "0".
		 */
		counter_u64_add(combined_wheel_wrap, 1);
		*target_tick = hpts->p_nxt_slot;
		return (0);
	} else {
		/* 
		 * We know how many slots are open
		 * on the wheel (the reverse of what
		 * is left to run. Take away the time
		 * the pacer started to now (wheel_tick)
		 * and that tells you how many slots are
		 * open that can be inserted into that won't
		 * be touched by the pacer until later.
		 */
		return (avail_on_wheel - pacer_to_now);
	}
}