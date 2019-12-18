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
struct pmc_hw {struct pmc* phw_pmc; } ;
struct pmc {int dummy; } ;
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_2__ {struct pmc_hw* pc_ppcpmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMLCax_FC ; 
 int /*<<< orphan*/  PMR_PMLCa0 ; 
 int /*<<< orphan*/  PMR_PMLCa1 ; 
 int /*<<< orphan*/  PMR_PMLCa2 ; 
 int /*<<< orphan*/  PMR_PMLCa3 ; 
 int /*<<< orphan*/  mfpmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** powerpc_pcpu ; 

__attribute__((used)) static int
e500_stop_pmc(int cpu, int ri)
{
        struct pmc *pm;
        struct pmc_hw *phw;
        register_t pmc_pmlc;

	phw    = &powerpc_pcpu[cpu]->pc_ppcpmcs[ri];
	pm     = phw->phw_pmc;

	/*
	 * Disable the PMCs.
	 */
	switch (ri) {
	case 0:
		pmc_pmlc = mfpmr(PMR_PMLCa0);
		pmc_pmlc |= PMLCax_FC;
		mtpmr(PMR_PMLCa0, pmc_pmlc);
		break;
	case 1:
		pmc_pmlc = mfpmr(PMR_PMLCa1);
		pmc_pmlc |= PMLCax_FC;
		mtpmr(PMR_PMLCa1, pmc_pmlc);
		break;
	case 2:
		pmc_pmlc = mfpmr(PMR_PMLCa2);
		pmc_pmlc |= PMLCax_FC;
		mtpmr(PMR_PMLCa2, pmc_pmlc);
		break;
	case 3:
		pmc_pmlc = mfpmr(PMR_PMLCa3);
		pmc_pmlc |= PMLCax_FC;
		mtpmr(PMR_PMLCa3, pmc_pmlc);
		break;
	default:
		break;
	}
	return 0;
}