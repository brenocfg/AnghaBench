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
struct teo_cpu {scalar_t__ sleep_length_ns; scalar_t__ time_span_ns; unsigned int* intervals; scalar_t__ interval_idx; TYPE_2__* states; } ;
struct cpuidle_driver {int state_count; TYPE_1__* states; } ;
struct cpuidle_device {size_t last_state_idx; int /*<<< orphan*/  cpu; } ;
struct TYPE_4__ {unsigned int early_hits; unsigned int hits; unsigned int misses; } ;
struct TYPE_3__ {unsigned int exit_latency; unsigned int target_residency; } ;

/* Variables and functions */
 unsigned int DECAY_SHIFT ; 
 scalar_t__ INTERVALS ; 
 scalar_t__ PULSE ; 
 unsigned int UINT_MAX ; 
 unsigned int ktime_to_us (scalar_t__) ; 
 struct teo_cpu* per_cpu_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  teo_cpus ; 

__attribute__((used)) static void teo_update(struct cpuidle_driver *drv, struct cpuidle_device *dev)
{
	struct teo_cpu *cpu_data = per_cpu_ptr(&teo_cpus, dev->cpu);
	unsigned int sleep_length_us = ktime_to_us(cpu_data->sleep_length_ns);
	int i, idx_hit = -1, idx_timer = -1;
	unsigned int measured_us;

	if (cpu_data->time_span_ns >= cpu_data->sleep_length_ns) {
		/*
		 * One of the safety nets has triggered or the wakeup was close
		 * enough to the closest timer event expected at the idle state
		 * selection time to be discarded.
		 */
		measured_us = UINT_MAX;
	} else {
		unsigned int lat;

		lat = drv->states[dev->last_state_idx].exit_latency;

		measured_us = ktime_to_us(cpu_data->time_span_ns);
		/*
		 * The delay between the wakeup and the first instruction
		 * executed by the CPU is not likely to be worst-case every
		 * time, so take 1/2 of the exit latency as a very rough
		 * approximation of the average of it.
		 */
		if (measured_us >= lat)
			measured_us -= lat / 2;
		else
			measured_us /= 2;
	}

	/*
	 * Decay the "early hits" metric for all of the states and find the
	 * states matching the sleep length and the measured idle duration.
	 */
	for (i = 0; i < drv->state_count; i++) {
		unsigned int early_hits = cpu_data->states[i].early_hits;

		cpu_data->states[i].early_hits -= early_hits >> DECAY_SHIFT;

		if (drv->states[i].target_residency <= sleep_length_us) {
			idx_timer = i;
			if (drv->states[i].target_residency <= measured_us)
				idx_hit = i;
		}
	}

	/*
	 * Update the "hits" and "misses" data for the state matching the sleep
	 * length.  If it matches the measured idle duration too, this is a hit,
	 * so increase the "hits" metric for it then.  Otherwise, this is a
	 * miss, so increase the "misses" metric for it.  In the latter case
	 * also increase the "early hits" metric for the state that actually
	 * matches the measured idle duration.
	 */
	if (idx_timer >= 0) {
		unsigned int hits = cpu_data->states[idx_timer].hits;
		unsigned int misses = cpu_data->states[idx_timer].misses;

		hits -= hits >> DECAY_SHIFT;
		misses -= misses >> DECAY_SHIFT;

		if (idx_timer > idx_hit) {
			misses += PULSE;
			if (idx_hit >= 0)
				cpu_data->states[idx_hit].early_hits += PULSE;
		} else {
			hits += PULSE;
		}

		cpu_data->states[idx_timer].misses = misses;
		cpu_data->states[idx_timer].hits = hits;
	}

	/*
	 * Save idle duration values corresponding to non-timer wakeups for
	 * pattern detection.
	 */
	cpu_data->intervals[cpu_data->interval_idx++] = measured_us;
	if (cpu_data->interval_idx > INTERVALS)
		cpu_data->interval_idx = 0;
}