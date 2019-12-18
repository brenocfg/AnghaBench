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
struct pt_regs {int dummy; } ;
struct TYPE_2__ {scalar_t__ pmc_type; } ;

/* Variables and functions */
 int MMCR0_PMAO ; 
 int MMCR0_PMXE ; 
 int PMGC0_PMIE ; 
 int /*<<< orphan*/  PMRN_PMGC0 ; 
 scalar_t__ PPC_PMC_IBM ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 TYPE_1__* cur_cpu_spec ; 
 int mfpmr (int /*<<< orphan*/ ) ; 
 int mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtpmr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void dummy_perf(struct pt_regs *regs)
{
#if defined(CONFIG_FSL_EMB_PERFMON)
	mtpmr(PMRN_PMGC0, mfpmr(PMRN_PMGC0) & ~PMGC0_PMIE);
#elif defined(CONFIG_PPC64) || defined(CONFIG_PPC_BOOK3S_32)
	if (cur_cpu_spec->pmc_type == PPC_PMC_IBM)
		mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~(MMCR0_PMXE|MMCR0_PMAO));
#else
	mtspr(SPRN_MMCR0, mfspr(SPRN_MMCR0) & ~MMCR0_PMXE);
#endif
}