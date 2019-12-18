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
struct TYPE_2__ {struct pmc_hw* pc_mipspmcs; } ;

/* Variables and functions */
 TYPE_1__** mips_pcpu ; 
 int /*<<< orphan*/  mips_wr_perfcnt0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_perfcnt2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips_stop_pmc(int cpu, int ri)
{
        struct pmc *pm;
        struct pmc_hw *phw;

	phw    = &mips_pcpu[cpu]->pc_mipspmcs[ri];
	pm     = phw->phw_pmc;

	/*
	 * Disable the PMCs.
	 *
	 * Clearing the entire register turns the counter off as well
	 * as removes the previously sampled event.
	 */
	switch (ri) {
	case 0:
		mips_wr_perfcnt0(0);
		break;
	case 1:
		mips_wr_perfcnt2(0);
		break;
	default:
		break;
	}
	return 0;
}