#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct trapframe {int dummy; } ;
struct TYPE_8__ {int pm_iap_evsel; } ;
struct TYPE_9__ {TYPE_3__ pm_iap; } ;
struct TYPE_7__ {int pm_reloadcount; } ;
struct pmc {scalar_t__ pm_state; TYPE_4__ pm_md; TYPE_2__ pm_sc; } ;
struct core_cpu {TYPE_1__* pc_corepmcs; } ;
typedef  int pmc_value_t ;
struct TYPE_10__ {int /*<<< orphan*/  pm_intr_ignored; int /*<<< orphan*/  pm_intr_processed; } ;
struct TYPE_6__ {struct pmc* phw_pmc; } ;

/* Variables and functions */
 int IAP_EN ; 
 scalar_t__ IAP_EVSEL0 ; 
 int IAP_EVSEL_MASK ; 
 scalar_t__ IAP_PMC0 ; 
 int /*<<< orphan*/  INT ; 
 int /*<<< orphan*/  MDP ; 
 int /*<<< orphan*/  PMCDBG3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,size_t,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC_HR ; 
 int /*<<< orphan*/  PMC_IS_SAMPLING_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ PMC_STATE_RUNNING ; 
 int /*<<< orphan*/  PMC_TO_MODE (struct pmc*) ; 
 int /*<<< orphan*/  TRAPF_USERMODE (struct trapframe*) ; 
 int core_iap_npmc ; 
 scalar_t__ core_iap_wroffset ; 
 struct core_cpu** core_pcpu ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 size_t curcpu ; 
 int /*<<< orphan*/  iap_pmc_has_overflowed (int) ; 
 int iap_reload_count_to_perfctr_value (int) ; 
 int /*<<< orphan*/  lapic_reenable_pmc () ; 
 int pmc_process_interrupt (int /*<<< orphan*/ ,struct pmc*,struct trapframe*) ; 
 TYPE_5__ pmc_stats ; 
 int rdmsr (scalar_t__) ; 
 int /*<<< orphan*/  wrmsr (scalar_t__,int) ; 

__attribute__((used)) static int
core_intr(struct trapframe *tf)
{
	pmc_value_t v;
	struct pmc *pm;
	struct core_cpu *cc;
	int error, found_interrupt, ri;
	uint64_t msr;

	PMCDBG3(MDP,INT, 1, "cpu=%d tf=0x%p um=%d", curcpu, (void *) tf,
	    TRAPF_USERMODE(tf));

	found_interrupt = 0;
	cc = core_pcpu[curcpu];

	for (ri = 0; ri < core_iap_npmc; ri++) {

		if ((pm = cc->pc_corepmcs[ri].phw_pmc) == NULL ||
		    !PMC_IS_SAMPLING_MODE(PMC_TO_MODE(pm)))
			continue;

		if (!iap_pmc_has_overflowed(ri))
			continue;

		found_interrupt = 1;

		if (pm->pm_state != PMC_STATE_RUNNING)
			continue;

		error = pmc_process_interrupt(PMC_HR, pm, tf);

		v = pm->pm_sc.pm_reloadcount;
		v = iap_reload_count_to_perfctr_value(v);

		/*
		 * Stop the counter, reload it but only restart it if
		 * the PMC is not stalled.
		 */
		msr = rdmsr(IAP_EVSEL0 + ri) & ~IAP_EVSEL_MASK;
		wrmsr(IAP_EVSEL0 + ri, msr);
		wrmsr(core_iap_wroffset + IAP_PMC0 + ri, v);

		if (error)
			continue;

		wrmsr(IAP_EVSEL0 + ri, msr | (pm->pm_md.pm_iap.pm_iap_evsel |
					      IAP_EN));
	}

	if (found_interrupt)
		lapic_reenable_pmc();

	if (found_interrupt)
		counter_u64_add(pmc_stats.pm_intr_processed, 1);
	else
		counter_u64_add(pmc_stats.pm_intr_ignored, 1);

	return (found_interrupt);
}