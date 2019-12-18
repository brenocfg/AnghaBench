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
struct perf_event {int dummy; } ;
struct cpu_hw_events {int pebs_enabled; } ;

/* Variables and functions */
 int PEBS_VIA_PT_MASK ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  is_pebs_pt (struct perf_event*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void intel_pmu_pebs_via_pt_disable(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	if (!is_pebs_pt(event))
		return;

	if (!(cpuc->pebs_enabled & ~PEBS_VIA_PT_MASK))
		cpuc->pebs_enabled &= ~PEBS_VIA_PT_MASK;
}