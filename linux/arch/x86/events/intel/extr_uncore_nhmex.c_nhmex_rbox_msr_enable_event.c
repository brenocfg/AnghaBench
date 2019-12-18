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
struct hw_perf_event_extra {int idx; int config; } ;
struct hw_perf_event {int config; int /*<<< orphan*/  config_base; struct hw_perf_event_extra branch_reg; struct hw_perf_event_extra extra_reg; } ;
struct perf_event {struct hw_perf_event hw; } ;
struct intel_uncore_box {TYPE_1__* pmu; } ;
struct TYPE_2__ {int pmu_idx; } ;

/* Variables and functions */
 int NHMEX_PMON_CTL_EN_BIT0 ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_IPERF_CFG0 (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_IPERF_CFG1 (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_QLX_CFG (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET1_MASK (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET1_MATCH (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET2_MASK (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET2_MATCH (int) ; 
 int /*<<< orphan*/  NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG (int) ; 
 int NHMEX_R_PMON_CTL_EV_SEL_MASK ; 
 int uncore_shared_reg_config (struct intel_uncore_box*,int) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void nhmex_rbox_msr_enable_event(struct intel_uncore_box *box, struct perf_event *event)
{
	struct hw_perf_event *hwc = &event->hw;
	struct hw_perf_event_extra *reg1 = &hwc->extra_reg;
	struct hw_perf_event_extra *reg2 = &hwc->branch_reg;
	int idx, port;

	idx = reg1->idx;
	port = idx / 6 + box->pmu->pmu_idx * 4;

	switch (idx % 6) {
	case 0:
		wrmsrl(NHMEX_R_MSR_PORTN_IPERF_CFG0(port), reg1->config);
		break;
	case 1:
		wrmsrl(NHMEX_R_MSR_PORTN_IPERF_CFG1(port), reg1->config);
		break;
	case 2:
	case 3:
		wrmsrl(NHMEX_R_MSR_PORTN_QLX_CFG(port),
			uncore_shared_reg_config(box, 2 + (idx / 6) * 5));
		break;
	case 4:
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET1_MM_CFG(port),
			hwc->config >> 32);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET1_MATCH(port), reg1->config);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET1_MASK(port), reg2->config);
		break;
	case 5:
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET2_MM_CFG(port),
			hwc->config >> 32);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET2_MATCH(port), reg1->config);
		wrmsrl(NHMEX_R_MSR_PORTN_XBR_SET2_MASK(port), reg2->config);
		break;
	}

	wrmsrl(hwc->config_base, NHMEX_PMON_CTL_EN_BIT0 |
		(hwc->config & NHMEX_R_PMON_CTL_EV_SEL_MASK));
}