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
typedef  int uint64_t ;
struct menu_device {unsigned int next_timer_us; size_t bucket; int* correction_factor; scalar_t__ needs_update; } ;
struct cpuidle_state_usage {scalar_t__ disable; } ;
struct cpuidle_state {unsigned int target_residency; int exit_latency; int flags; scalar_t__ disabled; } ;
struct cpuidle_driver {int state_count; struct cpuidle_state* states; } ;
struct cpuidle_device {struct cpuidle_state_usage* states_usage; int /*<<< orphan*/  cpu; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int CPUIDLE_FLAG_POLLING ; 
 int DECAY ; 
 unsigned int DIV_ROUND_CLOSEST_ULL (int,int) ; 
 int RESOLUTION ; 
 unsigned int TICK_USEC ; 
 int cpuidle_governor_latency_req (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_typical_interval (struct menu_device*,unsigned int) ; 
 void* ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_devices ; 
 int /*<<< orphan*/  menu_update (struct cpuidle_driver*,struct cpuidle_device*) ; 
 unsigned int min (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long nr_iowait_cpu (int /*<<< orphan*/ ) ; 
 unsigned int performance_multiplier (unsigned long) ; 
 struct menu_device* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tick_nohz_get_sleep_length (int /*<<< orphan*/ *) ; 
 scalar_t__ tick_nohz_tick_stopped () ; 
 scalar_t__ unlikely (int) ; 
 size_t which_bucket (unsigned int,unsigned long) ; 

__attribute__((used)) static int menu_select(struct cpuidle_driver *drv, struct cpuidle_device *dev,
		       bool *stop_tick)
{
	struct menu_device *data = this_cpu_ptr(&menu_devices);
	int latency_req = cpuidle_governor_latency_req(dev->cpu);
	int i;
	int idx;
	unsigned int interactivity_req;
	unsigned int predicted_us;
	unsigned long nr_iowaiters;
	ktime_t delta_next;

	if (data->needs_update) {
		menu_update(drv, dev);
		data->needs_update = 0;
	}

	/* determine the expected residency time, round up */
	data->next_timer_us = ktime_to_us(tick_nohz_get_sleep_length(&delta_next));

	nr_iowaiters = nr_iowait_cpu(dev->cpu);
	data->bucket = which_bucket(data->next_timer_us, nr_iowaiters);

	if (unlikely(drv->state_count <= 1 || latency_req == 0) ||
	    ((data->next_timer_us < drv->states[1].target_residency ||
	      latency_req < drv->states[1].exit_latency) &&
	     !drv->states[0].disabled && !dev->states_usage[0].disable)) {
		/*
		 * In this case state[0] will be used no matter what, so return
		 * it right away and keep the tick running if state[0] is a
		 * polling one.
		 */
		*stop_tick = !(drv->states[0].flags & CPUIDLE_FLAG_POLLING);
		return 0;
	}

	/*
	 * Force the result of multiplication to be 64 bits even if both
	 * operands are 32 bits.
	 * Make sure to round up for half microseconds.
	 */
	predicted_us = DIV_ROUND_CLOSEST_ULL((uint64_t)data->next_timer_us *
					 data->correction_factor[data->bucket],
					 RESOLUTION * DECAY);
	/*
	 * Use the lowest expected idle interval to pick the idle state.
	 */
	predicted_us = min(predicted_us, get_typical_interval(data, predicted_us));

	if (tick_nohz_tick_stopped()) {
		/*
		 * If the tick is already stopped, the cost of possible short
		 * idle duration misprediction is much higher, because the CPU
		 * may be stuck in a shallow idle state for a long time as a
		 * result of it.  In that case say we might mispredict and use
		 * the known time till the closest timer event for the idle
		 * state selection.
		 */
		if (predicted_us < TICK_USEC)
			predicted_us = ktime_to_us(delta_next);
	} else {
		/*
		 * Use the performance multiplier and the user-configurable
		 * latency_req to determine the maximum exit latency.
		 */
		interactivity_req = predicted_us / performance_multiplier(nr_iowaiters);
		if (latency_req > interactivity_req)
			latency_req = interactivity_req;
	}

	/*
	 * Find the idle state with the lowest power while satisfying
	 * our constraints.
	 */
	idx = -1;
	for (i = 0; i < drv->state_count; i++) {
		struct cpuidle_state *s = &drv->states[i];
		struct cpuidle_state_usage *su = &dev->states_usage[i];

		if (s->disabled || su->disable)
			continue;

		if (idx == -1)
			idx = i; /* first enabled state */

		if (s->target_residency > predicted_us) {
			/*
			 * Use a physical idle state, not busy polling, unless
			 * a timer is going to trigger soon enough.
			 */
			if ((drv->states[idx].flags & CPUIDLE_FLAG_POLLING) &&
			    s->exit_latency <= latency_req &&
			    s->target_residency <= data->next_timer_us) {
				predicted_us = s->target_residency;
				idx = i;
				break;
			}
			if (predicted_us < TICK_USEC)
				break;

			if (!tick_nohz_tick_stopped()) {
				/*
				 * If the state selected so far is shallow,
				 * waking up early won't hurt, so retain the
				 * tick in that case and let the governor run
				 * again in the next iteration of the loop.
				 */
				predicted_us = drv->states[idx].target_residency;
				break;
			}

			/*
			 * If the state selected so far is shallow and this
			 * state's target residency matches the time till the
			 * closest timer event, select this one to avoid getting
			 * stuck in the shallow one for too long.
			 */
			if (drv->states[idx].target_residency < TICK_USEC &&
			    s->target_residency <= ktime_to_us(delta_next))
				idx = i;

			return idx;
		}
		if (s->exit_latency > latency_req)
			break;

		idx = i;
	}

	if (idx == -1)
		idx = 0; /* No states enabled. Must use 0. */

	/*
	 * Don't stop the tick if the selected state is a polling one or if the
	 * expected idle duration is shorter than the tick period length.
	 */
	if (((drv->states[idx].flags & CPUIDLE_FLAG_POLLING) ||
	     predicted_us < TICK_USEC) && !tick_nohz_tick_stopped()) {
		unsigned int delta_next_us = ktime_to_us(delta_next);

		*stop_tick = false;

		if (idx > 0 && drv->states[idx].target_residency > delta_next_us) {
			/*
			 * The tick is not going to be stopped and the target
			 * residency of the state to be returned is not within
			 * the time until the next timer event including the
			 * tick, so try to correct that.
			 */
			for (i = idx - 1; i >= 0; i--) {
				if (drv->states[i].disabled ||
				    dev->states_usage[i].disable)
					continue;

				idx = i;
				if (drv->states[i].target_residency <= delta_next_us)
					break;
			}
		}
	}

	return idx;
}