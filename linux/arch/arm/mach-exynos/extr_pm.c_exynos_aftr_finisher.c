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
 int ENOSYS ; 
 int /*<<< orphan*/  FW_DO_IDLE_AFTR ; 
 int /*<<< orphan*/  S5P_CHECK_AFTR ; 
 int /*<<< orphan*/  SYS_AFTR ; 
 int call_firmware_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  do_idle ; 
 int /*<<< orphan*/  exynos_cpu_save_register () ; 
 int /*<<< orphan*/  exynos_cpu_set_boot_vector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_set_wakeupmask (int) ; 
 int /*<<< orphan*/  exynos_sys_powerdown_conf (int /*<<< orphan*/ ) ; 
 scalar_t__ read_cpuid_part () ; 
 scalar_t__ soc_is_exynos3250 () ; 

__attribute__((used)) static int exynos_aftr_finisher(unsigned long flags)
{
	int ret;

	exynos_set_wakeupmask(soc_is_exynos3250() ? 0x40003ffe : 0x0000ff3e);
	/* Set value of power down register for aftr mode */
	exynos_sys_powerdown_conf(SYS_AFTR);

	ret = call_firmware_op(do_idle, FW_DO_IDLE_AFTR);
	if (ret == -ENOSYS) {
		if (read_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
			exynos_cpu_save_register();
		exynos_cpu_set_boot_vector(S5P_CHECK_AFTR);
		cpu_do_idle();
	}

	return 1;
}