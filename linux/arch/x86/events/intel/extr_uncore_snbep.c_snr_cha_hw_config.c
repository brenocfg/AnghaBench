#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int config1; } ;
struct hw_perf_event_extra {int config; scalar_t__ idx; scalar_t__ reg; } ;
struct TYPE_6__ {struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_1__ attr; TYPE_2__ hw; } ;
struct intel_uncore_box {TYPE_4__* pmu; } ;
struct TYPE_8__ {int pmu_idx; TYPE_3__* type; } ;
struct TYPE_7__ {int msr_offset; } ;

/* Variables and functions */
 int SKX_CHA_MSR_PMON_BOX_FILTER_TID ; 
 scalar_t__ SNR_C0_MSR_PMON_BOX_FILTER0 ; 

__attribute__((used)) static int snr_cha_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event_extra *reg1 = &event->hw.extra_reg;

	reg1->reg = SNR_C0_MSR_PMON_BOX_FILTER0 +
		    box->pmu->type->msr_offset * box->pmu->pmu_idx;
	reg1->config = event->attr.config1 & SKX_CHA_MSR_PMON_BOX_FILTER_TID;
	reg1->idx = 0;

	return 0;
}