#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct pmc_mdep {int dummy; } ;
struct TYPE_3__ {struct TYPE_3__* pc_ppcpmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PMC ; 
 int /*<<< orphan*/  PMGC_FAC ; 
 int /*<<< orphan*/  PMR_PMGC0 ; 
 int PSL_PMM ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int mfmsr () ; 
 int /*<<< orphan*/  mfpmr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtmsr (int) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** powerpc_pcpu ; 

__attribute__((used)) static int
e500_pcpu_fini(struct pmc_mdep *md, int cpu)
{
	uint32_t pmgc0 = mfpmr(PMR_PMGC0);

	pmgc0 |= PMGC_FAC;
	mtpmr(PMR_PMGC0, pmgc0);
	mtmsr(mfmsr() & ~PSL_PMM);

	free(powerpc_pcpu[cpu]->pc_ppcpmcs, M_PMC);
	free(powerpc_pcpu[cpu], M_PMC);

	return 0;
}