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
typedef  void* u64 ;
struct TYPE_2__ {void* time; } ;
struct cpudata {int sched_flags; void* last_io_update; TYPE_1__ sample; } ;

/* Variables and functions */
 int SCHED_CPUFREQ_IOWAIT ; 
 int TICK_NSEC ; 
 int /*<<< orphan*/  intel_pstate_hwp_boost_down (struct cpudata*) ; 
 int /*<<< orphan*/  intel_pstate_hwp_boost_up (struct cpudata*) ; 
 scalar_t__ time_before64 (void*,void*) ; 

__attribute__((used)) static inline void intel_pstate_update_util_hwp_local(struct cpudata *cpu,
						      u64 time)
{
	cpu->sample.time = time;

	if (cpu->sched_flags & SCHED_CPUFREQ_IOWAIT) {
		bool do_io = false;

		cpu->sched_flags = 0;
		/*
		 * Set iowait_boost flag and update time. Since IO WAIT flag
		 * is set all the time, we can't just conclude that there is
		 * some IO bound activity is scheduled on this CPU with just
		 * one occurrence. If we receive at least two in two
		 * consecutive ticks, then we treat as boost candidate.
		 */
		if (time_before64(time, cpu->last_io_update + 2 * TICK_NSEC))
			do_io = true;

		cpu->last_io_update = time;

		if (do_io)
			intel_pstate_hwp_boost_up(cpu);

	} else {
		intel_pstate_hwp_boost_down(cpu);
	}
}