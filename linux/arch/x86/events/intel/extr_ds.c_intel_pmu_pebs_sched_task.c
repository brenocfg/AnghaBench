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
struct perf_event_context {int dummy; } ;
struct cpu_hw_events {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_drain_pebs_buffer () ; 
 scalar_t__ pebs_needs_sched_cb (struct cpu_hw_events*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void intel_pmu_pebs_sched_task(struct perf_event_context *ctx, bool sched_in)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	if (!sched_in && pebs_needs_sched_cb(cpuc))
		intel_pmu_drain_pebs_buffer();
}