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
struct perf_guest_switch_msr {int host; int guest; int /*<<< orphan*/  msr; } ;
struct cpu_hw_events {int intel_ctrl_guest_mask; int intel_ctrl_host_mask; int pebs_enabled; struct perf_guest_switch_msr* guest_switch_msrs; } ;
struct TYPE_2__ {int intel_ctrl; int flags; scalar_t__ pebs_no_isolation; scalar_t__ pebs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_CORE_PERF_GLOBAL_CTRL ; 
 int /*<<< orphan*/  MSR_IA32_PEBS_ENABLE ; 
 int PEBS_COUNTER_MASK ; 
 int PMU_FL_PEBS_ALL ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static struct perf_guest_switch_msr *intel_guest_get_msrs(int *nr)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct perf_guest_switch_msr *arr = cpuc->guest_switch_msrs;

	arr[0].msr = MSR_CORE_PERF_GLOBAL_CTRL;
	arr[0].host = x86_pmu.intel_ctrl & ~cpuc->intel_ctrl_guest_mask;
	arr[0].guest = x86_pmu.intel_ctrl & ~cpuc->intel_ctrl_host_mask;
	if (x86_pmu.flags & PMU_FL_PEBS_ALL)
		arr[0].guest &= ~cpuc->pebs_enabled;
	else
		arr[0].guest &= ~(cpuc->pebs_enabled & PEBS_COUNTER_MASK);
	*nr = 1;

	if (x86_pmu.pebs && x86_pmu.pebs_no_isolation) {
		/*
		 * If PMU counter has PEBS enabled it is not enough to
		 * disable counter on a guest entry since PEBS memory
		 * write can overshoot guest entry and corrupt guest
		 * memory. Disabling PEBS solves the problem.
		 *
		 * Don't do this if the CPU already enforces it.
		 */
		arr[1].msr = MSR_IA32_PEBS_ENABLE;
		arr[1].host = cpuc->pebs_enabled;
		arr[1].guest = 0;
		*nr = 2;
	}

	return arr;
}