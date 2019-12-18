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
typedef  int u64 ;
struct perf_event_attr {int sample_type; int precise_ip; int sample_regs_intr; int config; } ;
struct perf_event {struct perf_event_attr attr; } ;
struct TYPE_2__ {int rtm_abort_event; int lbr_nr; } ;

/* Variables and functions */
 int INTEL_ARCH_EVENT_MASK ; 
 int PEBS_DATACFG_GP ; 
 int PEBS_DATACFG_LBRS ; 
 int PEBS_DATACFG_LBR_SHIFT ; 
 int PEBS_DATACFG_MEMINFO ; 
 int PEBS_DATACFG_XMMS ; 
 int PEBS_GP_REGS ; 
 int PERF_PEBS_MEMINFO_TYPE ; 
 int PERF_REG_EXTENDED_MASK ; 
 int PERF_SAMPLE_BRANCH_STACK ; 
 int PERF_SAMPLE_IP ; 
 int PERF_SAMPLE_REGS_INTR ; 
 int PERF_SAMPLE_TIME ; 
 int PERF_SAMPLE_WEIGHT ; 
 TYPE_1__ x86_pmu ; 

__attribute__((used)) static u64 pebs_update_adaptive_cfg(struct perf_event *event)
{
	struct perf_event_attr *attr = &event->attr;
	u64 sample_type = attr->sample_type;
	u64 pebs_data_cfg = 0;
	bool gprs, tsx_weight;

	if (!(sample_type & ~(PERF_SAMPLE_IP|PERF_SAMPLE_TIME)) &&
	    attr->precise_ip > 1)
		return pebs_data_cfg;

	if (sample_type & PERF_PEBS_MEMINFO_TYPE)
		pebs_data_cfg |= PEBS_DATACFG_MEMINFO;

	/*
	 * We need GPRs when:
	 * + user requested them
	 * + precise_ip < 2 for the non event IP
	 * + For RTM TSX weight we need GPRs for the abort code.
	 */
	gprs = (sample_type & PERF_SAMPLE_REGS_INTR) &&
	       (attr->sample_regs_intr & PEBS_GP_REGS);

	tsx_weight = (sample_type & PERF_SAMPLE_WEIGHT) &&
		     ((attr->config & INTEL_ARCH_EVENT_MASK) ==
		      x86_pmu.rtm_abort_event);

	if (gprs || (attr->precise_ip < 2) || tsx_weight)
		pebs_data_cfg |= PEBS_DATACFG_GP;

	if ((sample_type & PERF_SAMPLE_REGS_INTR) &&
	    (attr->sample_regs_intr & PERF_REG_EXTENDED_MASK))
		pebs_data_cfg |= PEBS_DATACFG_XMMS;

	if (sample_type & PERF_SAMPLE_BRANCH_STACK) {
		/*
		 * For now always log all LBRs. Could configure this
		 * later.
		 */
		pebs_data_cfg |= PEBS_DATACFG_LBRS |
			((x86_pmu.lbr_nr-1) << PEBS_DATACFG_LBR_SHIFT);
	}

	return pebs_data_cfg;
}