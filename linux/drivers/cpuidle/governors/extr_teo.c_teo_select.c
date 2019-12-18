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
typedef  unsigned int u64 ;
struct teo_cpu {unsigned int* intervals; TYPE_1__* states; int /*<<< orphan*/  sleep_length_ns; int /*<<< orphan*/  time_span_ns; } ;
struct cpuidle_state_usage {scalar_t__ disable; } ;
struct cpuidle_state {unsigned int target_residency; int exit_latency; int flags; scalar_t__ disabled; } ;
struct cpuidle_driver {int state_count; struct cpuidle_state* states; } ;
struct cpuidle_device {int last_state_idx; struct cpuidle_state_usage* states_usage; int /*<<< orphan*/  cpu; } ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_2__ {unsigned int early_hits; scalar_t__ hits; scalar_t__ misses; } ;

/* Variables and functions */
 int CPUIDLE_FLAG_POLLING ; 
 int INTERVALS ; 
 unsigned int TICK_USEC ; 
 int cpuidle_governor_latency_req (int /*<<< orphan*/ ) ; 
 unsigned int div64_u64 (unsigned int,unsigned int) ; 
 unsigned int ktime_to_us (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_clock () ; 
 struct teo_cpu* per_cpu_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teo_cpus ; 
 int teo_find_shallower_state (struct cpuidle_driver*,struct cpuidle_device*,int,unsigned int) ; 
 int /*<<< orphan*/  teo_update (struct cpuidle_driver*,struct cpuidle_device*) ; 
 int /*<<< orphan*/  tick_nohz_get_sleep_length (int /*<<< orphan*/ *) ; 
 scalar_t__ tick_nohz_tick_stopped () ; 

__attribute__((used)) static int teo_select(struct cpuidle_driver *drv, struct cpuidle_device *dev,
		      bool *stop_tick)
{
	struct teo_cpu *cpu_data = per_cpu_ptr(&teo_cpus, dev->cpu);
	int latency_req = cpuidle_governor_latency_req(dev->cpu);
	unsigned int duration_us, count;
	int max_early_idx, constraint_idx, idx, i;
	ktime_t delta_tick;

	if (dev->last_state_idx >= 0) {
		teo_update(drv, dev);
		dev->last_state_idx = -1;
	}

	cpu_data->time_span_ns = local_clock();

	cpu_data->sleep_length_ns = tick_nohz_get_sleep_length(&delta_tick);
	duration_us = ktime_to_us(cpu_data->sleep_length_ns);

	count = 0;
	max_early_idx = -1;
	constraint_idx = drv->state_count;
	idx = -1;

	for (i = 0; i < drv->state_count; i++) {
		struct cpuidle_state *s = &drv->states[i];
		struct cpuidle_state_usage *su = &dev->states_usage[i];

		if (s->disabled || su->disable) {
			/*
			 * If the "early hits" metric of a disabled state is
			 * greater than the current maximum, it should be taken
			 * into account, because it would be a mistake to select
			 * a deeper state with lower "early hits" metric.  The
			 * index cannot be changed to point to it, however, so
			 * just increase the max count alone and let the index
			 * still point to a shallower idle state.
			 */
			if (max_early_idx >= 0 &&
			    count < cpu_data->states[i].early_hits)
				count = cpu_data->states[i].early_hits;

			continue;
		}

		if (idx < 0)
			idx = i; /* first enabled state */

		if (s->target_residency > duration_us)
			break;

		if (s->exit_latency > latency_req && constraint_idx > i)
			constraint_idx = i;

		idx = i;

		if (count < cpu_data->states[i].early_hits &&
		    !(tick_nohz_tick_stopped() &&
		      drv->states[i].target_residency < TICK_USEC)) {
			count = cpu_data->states[i].early_hits;
			max_early_idx = i;
		}
	}

	/*
	 * If the "hits" metric of the idle state matching the sleep length is
	 * greater than its "misses" metric, that is the one to use.  Otherwise,
	 * it is more likely that one of the shallower states will match the
	 * idle duration observed after wakeup, so take the one with the maximum
	 * "early hits" metric, but if that cannot be determined, just use the
	 * state selected so far.
	 */
	if (cpu_data->states[idx].hits <= cpu_data->states[idx].misses &&
	    max_early_idx >= 0) {
		idx = max_early_idx;
		duration_us = drv->states[idx].target_residency;
	}

	/*
	 * If there is a latency constraint, it may be necessary to use a
	 * shallower idle state than the one selected so far.
	 */
	if (constraint_idx < idx)
		idx = constraint_idx;

	if (idx < 0) {
		idx = 0; /* No states enabled. Must use 0. */
	} else if (idx > 0) {
		u64 sum = 0;

		count = 0;

		/*
		 * Count and sum the most recent idle duration values less than
		 * the current expected idle duration value.
		 */
		for (i = 0; i < INTERVALS; i++) {
			unsigned int val = cpu_data->intervals[i];

			if (val >= duration_us)
				continue;

			count++;
			sum += val;
		}

		/*
		 * Give up unless the majority of the most recent idle duration
		 * values are in the interesting range.
		 */
		if (count > INTERVALS / 2) {
			unsigned int avg_us = div64_u64(sum, count);

			/*
			 * Avoid spending too much time in an idle state that
			 * would be too shallow.
			 */
			if (!(tick_nohz_tick_stopped() && avg_us < TICK_USEC)) {
				duration_us = avg_us;
				if (drv->states[idx].target_residency > avg_us)
					idx = teo_find_shallower_state(drv, dev,
								       idx, avg_us);
			}
		}
	}

	/*
	 * Don't stop the tick if the selected state is a polling one or if the
	 * expected idle duration is shorter than the tick period length.
	 */
	if (((drv->states[idx].flags & CPUIDLE_FLAG_POLLING) ||
	    duration_us < TICK_USEC) && !tick_nohz_tick_stopped()) {
		unsigned int delta_tick_us = ktime_to_us(delta_tick);

		*stop_tick = false;

		/*
		 * The tick is not going to be stopped, so if the target
		 * residency of the state to be returned is not within the time
		 * till the closest timer including the tick, try to correct
		 * that.
		 */
		if (idx > 0 && drv->states[idx].target_residency > delta_tick_us)
			idx = teo_find_shallower_state(drv, dev, idx, delta_tick_us);
	}

	return idx;
}