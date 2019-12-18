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
struct pmu {int dummy; } ;
struct cpu_hw_events {int disabled; int pmcs_enabled; int* mmcr; scalar_t__ n_added; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 unsigned long MMCR0_BHRBA ; 
 unsigned long MMCR0_EBE ; 
 unsigned long MMCR0_FC ; 
 unsigned long MMCR0_FC56 ; 
 unsigned long MMCR0_PMAO ; 
 unsigned long MMCR0_PMCC ; 
 int MMCRA_SAMPLE_ENABLE ; 
 int PPMU_ARCH_207S ; 
 int /*<<< orphan*/  SPRN_MMCR0 ; 
 int /*<<< orphan*/  SPRN_MMCRA ; 
 int /*<<< orphan*/  SPRN_SDAR ; 
 int /*<<< orphan*/  SPRN_SIAR ; 
 int /*<<< orphan*/  cpu_hw_events ; 
 int /*<<< orphan*/  ebb_switch_out (unsigned long) ; 
 int /*<<< orphan*/  isync () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  mb () ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtspr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ppc_enable_pmcs () ; 
 TYPE_1__* ppmu ; 
 struct cpu_hw_events* this_cpu_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_mmcr0 (struct cpu_hw_events*,unsigned long) ; 

__attribute__((used)) static void power_pmu_disable(struct pmu *pmu)
{
	struct cpu_hw_events *cpuhw;
	unsigned long flags, mmcr0, val;

	if (!ppmu)
		return;
	local_irq_save(flags);
	cpuhw = this_cpu_ptr(&cpu_hw_events);

	if (!cpuhw->disabled) {
		/*
		 * Check if we ever enabled the PMU on this cpu.
		 */
		if (!cpuhw->pmcs_enabled) {
			ppc_enable_pmcs();
			cpuhw->pmcs_enabled = 1;
		}

		/*
		 * Set the 'freeze counters' bit, clear EBE/BHRBA/PMCC/PMAO/FC56
		 */
		val  = mmcr0 = mfspr(SPRN_MMCR0);
		val |= MMCR0_FC;
		val &= ~(MMCR0_EBE | MMCR0_BHRBA | MMCR0_PMCC | MMCR0_PMAO |
			 MMCR0_FC56);

		/*
		 * The barrier is to make sure the mtspr has been
		 * executed and the PMU has frozen the events etc.
		 * before we return.
		 */
		write_mmcr0(cpuhw, val);
		mb();
		isync();

		/*
		 * Disable instruction sampling if it was enabled
		 */
		if (cpuhw->mmcr[2] & MMCRA_SAMPLE_ENABLE) {
			mtspr(SPRN_MMCRA,
			      cpuhw->mmcr[2] & ~MMCRA_SAMPLE_ENABLE);
			mb();
			isync();
		}

		cpuhw->disabled = 1;
		cpuhw->n_added = 0;

		ebb_switch_out(mmcr0);

#ifdef CONFIG_PPC64
		/*
		 * These are readable by userspace, may contain kernel
		 * addresses and are not switched by context switch, so clear
		 * them now to avoid leaking anything to userspace in general
		 * including to another process.
		 */
		if (ppmu->flags & PPMU_ARCH_207S) {
			mtspr(SPRN_SDAR, 0);
			mtspr(SPRN_SIAR, 0);
		}
#endif
	}

	local_irq_restore(flags);
}