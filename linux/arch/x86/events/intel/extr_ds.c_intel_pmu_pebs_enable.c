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
typedef  int u64 ;
struct hw_perf_event {unsigned long long idx; int flags; scalar_t__ sample_period; int /*<<< orphan*/  config; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct debug_store {int* pebs_event_reset; } ;
struct cpu_hw_events {unsigned long long pebs_enabled; scalar_t__ pebs_data_cfg; scalar_t__ active_pebs_data_cfg; struct debug_store* ds; } ;
struct TYPE_3__ {scalar_t__ pebs_baseline; } ;
struct TYPE_4__ {int version; int cntval_mask; TYPE_1__ intel_cap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARCH_PERFMON_EVENTSEL_INT ; 
 int /*<<< orphan*/  ICL_EVENTSEL_ADAPTIVE ; 
 unsigned int INTEL_PMC_IDX_FIXED ; 
 unsigned int MAX_PEBS_EVENTS ; 
 int /*<<< orphan*/  MSR_PEBS_DATA_CFG ; 
 int PERF_X86_EVENT_AUTO_RELOAD ; 
 int PERF_X86_EVENT_PEBS_LDLAT ; 
 int PERF_X86_EVENT_PEBS_ST ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  intel_pmu_pebs_via_pt_enable (struct perf_event*) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_2__ x86_pmu ; 

void intel_pmu_pebs_enable(struct perf_event *event)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;
	struct debug_store *ds = cpuc->ds;

	hwc->config &= ~ARCH_PERFMON_EVENTSEL_INT;

	cpuc->pebs_enabled |= 1ULL << hwc->idx;

	if ((event->hw.flags & PERF_X86_EVENT_PEBS_LDLAT) && (x86_pmu.version < 5))
		cpuc->pebs_enabled |= 1ULL << (hwc->idx + 32);
	else if (event->hw.flags & PERF_X86_EVENT_PEBS_ST)
		cpuc->pebs_enabled |= 1ULL << 63;

	if (x86_pmu.intel_cap.pebs_baseline) {
		hwc->config |= ICL_EVENTSEL_ADAPTIVE;
		if (cpuc->pebs_data_cfg != cpuc->active_pebs_data_cfg) {
			wrmsrl(MSR_PEBS_DATA_CFG, cpuc->pebs_data_cfg);
			cpuc->active_pebs_data_cfg = cpuc->pebs_data_cfg;
		}
	}

	/*
	 * Use auto-reload if possible to save a MSR write in the PMI.
	 * This must be done in pmu::start(), because PERF_EVENT_IOC_PERIOD.
	 */
	if (hwc->flags & PERF_X86_EVENT_AUTO_RELOAD) {
		unsigned int idx = hwc->idx;

		if (idx >= INTEL_PMC_IDX_FIXED)
			idx = MAX_PEBS_EVENTS + (idx - INTEL_PMC_IDX_FIXED);
		ds->pebs_event_reset[idx] =
			(u64)(-hwc->sample_period) & x86_pmu.cntval_mask;
	} else {
		ds->pebs_event_reset[hwc->idx] = 0;
	}

	intel_pmu_pebs_via_pt_enable(event);
}