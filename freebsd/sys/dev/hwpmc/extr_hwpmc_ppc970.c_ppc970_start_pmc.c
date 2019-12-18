#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct pmc_hw {struct pmc* phw_pmc; } ;
struct TYPE_4__ {int pm_powerpc_evsel; } ;
struct TYPE_5__ {TYPE_1__ pm_powerpc; } ;
struct pmc {TYPE_2__ pm_md; } ;
typedef  int register_t ;
struct TYPE_6__ {struct pmc_hw* pc_ppcpmcs; } ;

/* Variables and functions */
 int POWERPC_PMC_ENABLE ; 
 int /*<<< orphan*/  SPR_970MMCR0 ; 
 int SPR_MMCR0_FC ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 TYPE_3__** powerpc_pcpu ; 
 int ppc970_set_pmc (int,int,int) ; 

__attribute__((used)) static int
ppc970_start_pmc(int cpu, int ri)
{
	struct pmc *pm;
	struct pmc_hw *phw;
	register_t pmc_mmcr;
	uint32_t config;
	int error;

	phw    = &powerpc_pcpu[cpu]->pc_ppcpmcs[ri];
	pm     = phw->phw_pmc;
	config = pm->pm_md.pm_powerpc.pm_powerpc_evsel & ~POWERPC_PMC_ENABLE;

	error = ppc970_set_pmc(cpu, ri, config);
	
	/* The mask is inverted (enable is 1) compared to the flags in MMCR0, which
	 * are Freeze flags.
	 */
	config = ~pm->pm_md.pm_powerpc.pm_powerpc_evsel & POWERPC_PMC_ENABLE;

	pmc_mmcr = mfspr(SPR_970MMCR0);
	pmc_mmcr &= ~SPR_MMCR0_FC;
	pmc_mmcr |= config;
	mtspr(SPR_970MMCR0, pmc_mmcr);

	return 0;
}