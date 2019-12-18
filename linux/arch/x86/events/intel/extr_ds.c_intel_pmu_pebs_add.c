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
struct hw_perf_event {int flags; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct cpu_hw_events {int /*<<< orphan*/  n_pebs_via_pt; int /*<<< orphan*/  n_large_pebs; int /*<<< orphan*/  n_pebs; } ;

/* Variables and functions */
 int PERF_X86_EVENT_LARGE_PEBS ; 
 int PERF_X86_EVENT_PEBS_VIA_PT ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int pebs_needs_sched_cb (struct cpu_hw_events*) ; 
 int /*<<< orphan*/  pebs_update_state (int,struct cpu_hw_events*,struct perf_event*,int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

void intel_pmu_pebs_add(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;
	bool needed_cb = pebs_needs_sched_cb(cpuc);

	cpuc->n_pebs++;
	if (hwc->flags & PERF_X86_EVENT_LARGE_PEBS)
		cpuc->n_large_pebs++;
	if (hwc->flags & PERF_X86_EVENT_PEBS_VIA_PT)
		cpuc->n_pebs_via_pt++;

	pebs_update_state(needed_cb, cpuc, event, true);
}