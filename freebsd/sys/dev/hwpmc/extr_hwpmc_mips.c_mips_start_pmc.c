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
typedef  int /*<<< orphan*/  uint32_t ;
struct pmc_hw {struct pmc* phw_pmc; } ;
struct TYPE_3__ {int /*<<< orphan*/  pm_mips_evsel; } ;
struct pmc {TYPE_1__ pm_md; } ;
struct TYPE_4__ {struct pmc_hw* pc_mipspmcs; } ;

/* Variables and functions */
 TYPE_2__** mips_pcpu ; 
 int /*<<< orphan*/  mips_wr_perfcnt0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_wr_perfcnt2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mips_start_pmc(int cpu, int ri)
{
	uint32_t config;
        struct pmc *pm;
        struct pmc_hw *phw;

	phw    = &mips_pcpu[cpu]->pc_mipspmcs[ri];
	pm     = phw->phw_pmc;
	config = pm->pm_md.pm_mips_evsel;

	/* Enable the PMC. */
	switch (ri) {
	case 0:
		mips_wr_perfcnt0(config);
		break;
	case 1:
		mips_wr_perfcnt2(config);
		break;
	default:
		break;
	}

	return 0;
}