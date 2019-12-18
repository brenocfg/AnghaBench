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
struct menu_device {unsigned int next_timer_us; unsigned int* correction_factor; size_t bucket; unsigned int* intervals; scalar_t__ interval_ptr; scalar_t__ tick_wakeup; } ;
struct cpuidle_state {int flags; int exit_latency; } ;
struct cpuidle_driver {struct cpuidle_state* states; } ;
struct cpuidle_device {int last_state_idx; unsigned int last_residency; scalar_t__ poll_time_limit; } ;

/* Variables and functions */
 int CPUIDLE_FLAG_POLLING ; 
 unsigned int DECAY ; 
 scalar_t__ INTERVALS ; 
 int MAX_INTERESTING ; 
 unsigned int RESOLUTION ; 
 unsigned int TICK_USEC ; 
 int /*<<< orphan*/  menu_devices ; 
 struct menu_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void menu_update(struct cpuidle_driver *drv, struct cpuidle_device *dev)
{
	struct menu_device *data = this_cpu_ptr(&menu_devices);
	int last_idx = dev->last_state_idx;
	struct cpuidle_state *target = &drv->states[last_idx];
	unsigned int measured_us;
	unsigned int new_factor;

	/*
	 * Try to figure out how much time passed between entry to low
	 * power state and occurrence of the wakeup event.
	 *
	 * If the entered idle state didn't support residency measurements,
	 * we use them anyway if they are short, and if long,
	 * truncate to the whole expected time.
	 *
	 * Any measured amount of time will include the exit latency.
	 * Since we are interested in when the wakeup begun, not when it
	 * was completed, we must subtract the exit latency. However, if
	 * the measured amount of time is less than the exit latency,
	 * assume the state was never reached and the exit latency is 0.
	 */

	if (data->tick_wakeup && data->next_timer_us > TICK_USEC) {
		/*
		 * The nohz code said that there wouldn't be any events within
		 * the tick boundary (if the tick was stopped), but the idle
		 * duration predictor had a differing opinion.  Since the CPU
		 * was woken up by a tick (that wasn't stopped after all), the
		 * predictor was not quite right, so assume that the CPU could
		 * have been idle long (but not forever) to help the idle
		 * duration predictor do a better job next time.
		 */
		measured_us = 9 * MAX_INTERESTING / 10;
	} else if ((drv->states[last_idx].flags & CPUIDLE_FLAG_POLLING) &&
		   dev->poll_time_limit) {
		/*
		 * The CPU exited the "polling" state due to a time limit, so
		 * the idle duration prediction leading to the selection of that
		 * state was inaccurate.  If a better prediction had been made,
		 * the CPU might have been woken up from idle by the next timer.
		 * Assume that to be the case.
		 */
		measured_us = data->next_timer_us;
	} else {
		/* measured value */
		measured_us = dev->last_residency;

		/* Deduct exit latency */
		if (measured_us > 2 * target->exit_latency)
			measured_us -= target->exit_latency;
		else
			measured_us /= 2;
	}

	/* Make sure our coefficients do not exceed unity */
	if (measured_us > data->next_timer_us)
		measured_us = data->next_timer_us;

	/* Update our correction ratio */
	new_factor = data->correction_factor[data->bucket];
	new_factor -= new_factor / DECAY;

	if (data->next_timer_us > 0 && measured_us < MAX_INTERESTING)
		new_factor += RESOLUTION * measured_us / data->next_timer_us;
	else
		/*
		 * we were idle so long that we count it as a perfect
		 * prediction
		 */
		new_factor += RESOLUTION;

	/*
	 * We don't want 0 as factor; we always want at least
	 * a tiny bit of estimated time. Fortunately, due to rounding,
	 * new_factor will stay nonzero regardless of measured_us values
	 * and the compiler can eliminate this test as long as DECAY > 1.
	 */
	if (DECAY == 1 && unlikely(new_factor == 0))
		new_factor = 1;

	data->correction_factor[data->bucket] = new_factor;

	/* update the repeating-pattern data */
	data->intervals[data->interval_ptr++] = measured_us;
	if (data->interval_ptr >= INTERVALS)
		data->interval_ptr = 0;
}