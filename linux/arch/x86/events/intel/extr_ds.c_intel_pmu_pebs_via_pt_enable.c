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
struct hw_perf_event {int flags; size_t idx; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct debug_store {int /*<<< orphan*/ * pebs_event_reset; } ;
struct cpu_hw_events {int /*<<< orphan*/  pebs_enabled; struct debug_store* ds; } ;

/* Variables and functions */
 scalar_t__ MSR_RELOAD_PMC0 ; 
 int /*<<< orphan*/  PEBS_OUTPUT_PT ; 
 int /*<<< orphan*/  PEBS_PMI_AFTER_EACH_RECORD ; 
 int PERF_X86_EVENT_LARGE_PEBS ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  is_pebs_pt (struct perf_event*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void intel_pmu_pebs_via_pt_enable(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;
	struct debug_store *ds = cpuc->ds;

	if (!is_pebs_pt(event))
		return;

	if (!(event->hw.flags & PERF_X86_EVENT_LARGE_PEBS))
		cpuc->pebs_enabled |= PEBS_PMI_AFTER_EACH_RECORD;

	cpuc->pebs_enabled |= PEBS_OUTPUT_PT;

	wrmsrl(MSR_RELOAD_PMC0 + hwc->idx, ds->pebs_event_reset[hwc->idx]);
}