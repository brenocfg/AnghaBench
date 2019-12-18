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
typedef  int /*<<< orphan*/  uint32_t ;
struct pmc_hw {struct pmc* phw_pmc; } ;
struct TYPE_4__ {int /*<<< orphan*/  pm_powerpc_evsel; } ;
struct TYPE_5__ {TYPE_1__ pm_powerpc; } ;
struct pmc {TYPE_2__ pm_md; } ;
struct TYPE_6__ {struct pmc_hw* pc_ppcpmcs; } ;

/* Variables and functions */
 scalar_t__ PMC_IS_SAMPLING_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMC_TO_MODE (struct pmc*) ; 
 int /*<<< orphan*/  PMLCax_CE ; 
 int /*<<< orphan*/  PMR_PMLCa0 ; 
 int /*<<< orphan*/  PMR_PMLCa1 ; 
 int /*<<< orphan*/  PMR_PMLCa2 ; 
 int /*<<< orphan*/  PMR_PMLCa3 ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__** powerpc_pcpu ; 

__attribute__((used)) static int
e500_start_pmc(int cpu, int ri)
{
	uint32_t config;
        struct pmc *pm;
        struct pmc_hw *phw;

	phw    = &powerpc_pcpu[cpu]->pc_ppcpmcs[ri];
	pm     = phw->phw_pmc;
	config = pm->pm_md.pm_powerpc.pm_powerpc_evsel;

	if (PMC_IS_SAMPLING_MODE(PMC_TO_MODE(pm)))
		config |= PMLCax_CE;

	/* Enable the PMC. */
	switch (ri) {
	case 0:
		mtpmr(PMR_PMLCa0, config);
		break;
	case 1:
		mtpmr(PMR_PMLCa1, config);
		break;
	case 2:
		mtpmr(PMR_PMLCa2, config);
		break;
	case 3:
		mtpmr(PMR_PMLCa3, config);
		break;
	default:
		break;
	}
	
	return 0;
}