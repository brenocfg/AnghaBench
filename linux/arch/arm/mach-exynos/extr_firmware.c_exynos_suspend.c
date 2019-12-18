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
 scalar_t__ EXYNOS_BOOT_ADDR ; 
 scalar_t__ EXYNOS_BOOT_FLAG ; 
 int /*<<< orphan*/  EXYNOS_SLEEP_MAGIC ; 
 int /*<<< orphan*/  __pa_symbol (int /*<<< orphan*/ ) ; 
 int cpu_suspend (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_cpu_resume_ns ; 
 int /*<<< orphan*/  exynos_cpu_suspend ; 
 int /*<<< orphan*/  exynos_save_cp15 () ; 
 scalar_t__ read_cpuid_part () ; 
 scalar_t__ sysram_ns_base_addr ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int exynos_suspend(void)
{
	if (read_cpuid_part() == ARM_CPU_PART_CORTEX_A9)
		exynos_save_cp15();

	writel(EXYNOS_SLEEP_MAGIC, sysram_ns_base_addr + EXYNOS_BOOT_FLAG);
	writel(__pa_symbol(exynos_cpu_resume_ns),
		sysram_ns_base_addr + EXYNOS_BOOT_ADDR);

	return cpu_suspend(0, exynos_cpu_suspend);
}