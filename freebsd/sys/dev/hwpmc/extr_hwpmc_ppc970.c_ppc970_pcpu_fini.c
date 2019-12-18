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
struct pmc_mdep {int dummy; } ;
typedef  int /*<<< orphan*/  register_t ;
struct TYPE_3__ {struct TYPE_3__* pc_ppcpmcs; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_PMC ; 
 int /*<<< orphan*/  SPR_MMCR0 ; 
 int /*<<< orphan*/  SPR_MMCR0_FC ; 
 int /*<<< orphan*/  SPR_MMCR0_PMXE ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__** powerpc_pcpu ; 

__attribute__((used)) static int
ppc970_pcpu_fini(struct pmc_mdep *md, int cpu)
{
	register_t mmcr0 = mfspr(SPR_MMCR0);

	mmcr0 |= SPR_MMCR0_FC;
	mmcr0 &= ~SPR_MMCR0_PMXE;
	mtspr(SPR_MMCR0, mmcr0);

	free(powerpc_pcpu[cpu]->pc_ppcpmcs, M_PMC);
	free(powerpc_pcpu[cpu], M_PMC);

	return 0;
}