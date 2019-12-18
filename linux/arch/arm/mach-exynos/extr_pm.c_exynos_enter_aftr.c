#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ ARM_CPU_PART_CORTEX_A9 ; 
 int /*<<< orphan*/  C2_STATE ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  S5P_CENTRAL_SEQ_OPTION ; 
 int S5P_USE_STANDBY_WFE0 ; 
 int S5P_USE_STANDBY_WFI0 ; 
 int /*<<< orphan*/  call_firmware_op (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_pm_enter () ; 
 int /*<<< orphan*/  cpu_pm_exit () ; 
 int /*<<< orphan*/  cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_aftr_finisher ; 
 int /*<<< orphan*/  exynos_clear_boot_flag (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_cpu_restore_register () ; 
 int /*<<< orphan*/  exynos_pm_central_resume () ; 
 int /*<<< orphan*/  exynos_pm_central_suspend () ; 
 int /*<<< orphan*/  exynos_scu_enable () ; 
 int /*<<< orphan*/  exynos_set_boot_flag (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmu_raw_writel (int,int /*<<< orphan*/ ) ; 
 scalar_t__ read_cpuid_part () ; 
 int /*<<< orphan*/  resume ; 
 unsigned int smp_processor_id () ; 
 scalar_t__ soc_is_exynos3250 () ; 
 scalar_t__ soc_is_exynos4412 () ; 

void exynos_enter_aftr(void)
{
	unsigned int cpuid = smp_processor_id();

	cpu_pm_enter();

	if (soc_is_exynos3250())
		exynos_set_boot_flag(cpuid, C2_STATE);

	exynos_pm_central_suspend();

	if (soc_is_exynos4412()) {
		/* Setting SEQ_OPTION register */
		pmu_raw_writel(S5P_USE_STANDBY_WFI0 | S5P_USE_STANDBY_WFE0,
			       S5P_CENTRAL_SEQ_OPTION);
	}

	cpu_suspend(0, exynos_aftr_finisher);

	if (read_cpuid_part() == ARM_CPU_PART_CORTEX_A9) {
		exynos_scu_enable();
		if (call_firmware_op(resume) == -ENOSYS)
			exynos_cpu_restore_register();
	}

	exynos_pm_central_resume();

	if (soc_is_exynos3250())
		exynos_clear_boot_flag(cpuid, C2_STATE);

	cpu_pm_exit();
}