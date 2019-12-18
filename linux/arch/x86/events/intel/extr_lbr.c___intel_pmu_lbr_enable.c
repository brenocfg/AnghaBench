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
struct cpu_hw_events {TYPE_1__* lbr_sel; } ;
struct TYPE_4__ {int version; int lbr_sel_mask; } ;
struct TYPE_3__ {int config; } ;

/* Variables and functions */
 int DEBUGCTLMSR_FREEZE_LBRS_ON_PMI ; 
 int DEBUGCTLMSR_LBR ; 
 int LBR_CALL_STACK ; 
 int /*<<< orphan*/  MSR_IA32_DEBUGCTLMSR ; 
 int /*<<< orphan*/  MSR_LBR_SELECT ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ x86_pmu ; 

__attribute__((used)) static void __intel_pmu_lbr_enable(bool pmi)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	u64 debugctl, lbr_select = 0, orig_debugctl;

	/*
	 * No need to unfreeze manually, as v4 can do that as part
	 * of the GLOBAL_STATUS ack.
	 */
	if (pmi && x86_pmu.version >= 4)
		return;

	/*
	 * No need to reprogram LBR_SELECT in a PMI, as it
	 * did not change.
	 */
	if (cpuc->lbr_sel)
		lbr_select = cpuc->lbr_sel->config & x86_pmu.lbr_sel_mask;
	if (!pmi && cpuc->lbr_sel)
		wrmsrl(MSR_LBR_SELECT, lbr_select);

	rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
	orig_debugctl = debugctl;
	debugctl |= DEBUGCTLMSR_LBR;
	/*
	 * LBR callstack does not work well with FREEZE_LBRS_ON_PMI.
	 * If FREEZE_LBRS_ON_PMI is set, PMI near call/return instructions
	 * may cause superfluous increase/decrease of LBR_TOS.
	 */
	if (!(lbr_select & LBR_CALL_STACK))
		debugctl |= DEBUGCTLMSR_FREEZE_LBRS_ON_PMI;
	if (orig_debugctl != debugctl)
		wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
}