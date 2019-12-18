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
struct TYPE_4__ {int /*<<< orphan*/  config2; int /*<<< orphan*/  config1; } ;
struct hw_perf_event_extra {int /*<<< orphan*/  config; scalar_t__ idx; int /*<<< orphan*/  reg; } ;
struct hw_perf_event {int config; struct hw_perf_event_extra branch_reg; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {TYPE_2__ attr; struct hw_perf_event hw; } ;
struct intel_uncore_box {TYPE_1__* pmu; } ;
struct TYPE_3__ {scalar_t__ pmu_idx; } ;

/* Variables and functions */
 int NHMEX_PMON_CTL_EV_SEL_MASK ; 
 int /*<<< orphan*/  NHMEX_S0_MSR_MM_CFG ; 
 int /*<<< orphan*/  NHMEX_S1_MSR_MM_CFG ; 
 int NHMEX_S_EVENT_TO_R_PROG_EV ; 

__attribute__((used)) static int nhmex_sbox_hw_config(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	struct hw_perf_event_extra *reg2 = &hwc->branch_reg;

	/* only TO_R_PROG_EV event uses the match/mask register */
	if ((hwc->config & NHMEX_PMON_CTL_EV_SEL_MASK) !=
	    NHMEX_S_EVENT_TO_R_PROG_EV)
		return 0;

	if (box->pmu->pmu_idx == 0)
		reg1->reg = NHMEX_S0_MSR_MM_CFG;
	else
		reg1->reg = NHMEX_S1_MSR_MM_CFG;
	reg1->idx = 0;
	reg1->config = event->attr.config1;
	reg2->config = event->attr.config2;
	return 0;
}