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
struct TYPE_2__ {int precise_ip; } ;
struct hw_perf_event {unsigned long long idx; scalar_t__ config_base; } ;
struct perf_event {TYPE_1__ attr; struct hw_perf_event hw; } ;
struct cpu_hw_events {unsigned long long intel_ctrl_guest_mask; unsigned long long intel_ctrl_host_mask; unsigned long long intel_cp_status; } ;

/* Variables and functions */
 unsigned long long INTEL_PMC_IDX_FIXED_BTS ; 
 scalar_t__ MSR_ARCH_PERFMON_FIXED_CTR_CTRL ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_disable_bts () ; 
 int /*<<< orphan*/  intel_pmu_disable_fixed (struct hw_perf_event*) ; 
 int /*<<< orphan*/  intel_pmu_drain_bts_buffer () ; 
 int /*<<< orphan*/  intel_pmu_pebs_disable (struct perf_event*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  x86_pmu_disable_event (struct perf_event*) ; 

__attribute__((used)) static void intel_pmu_disable_event(struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	if (unlikely(hwc->idx == INTEL_PMC_IDX_FIXED_BTS)) {
		intel_pmu_disable_bts();
		intel_pmu_drain_bts_buffer();
		return;
	}

	cpuc->intel_ctrl_guest_mask &= ~(1ull << hwc->idx);
	cpuc->intel_ctrl_host_mask &= ~(1ull << hwc->idx);
	cpuc->intel_cp_status &= ~(1ull << hwc->idx);

	if (unlikely(hwc->config_base == MSR_ARCH_PERFMON_FIXED_CTR_CTRL))
		intel_pmu_disable_fixed(hwc);
	else
		x86_pmu_disable_event(event);

	/*
	 * Needs to be called after x86_pmu_disable_event,
	 * so we don't trigger the event without PEBS bit set.
	 */
	if (unlikely(event->attr.precise_ip))
		intel_pmu_pebs_disable(event);
}