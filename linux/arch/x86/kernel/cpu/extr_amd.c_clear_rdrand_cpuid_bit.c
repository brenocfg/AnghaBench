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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CONFIG_PM_SLEEP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_AMD64_CPUID_FN_1 ; 
 int /*<<< orphan*/  X86_FEATURE_RDRAND ; 
 int /*<<< orphan*/  clear_cpu_cap (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int cpuid_ecx (int) ; 
 int /*<<< orphan*/  msr_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_info_once (char*) ; 
 scalar_t__ rdrand_force ; 

__attribute__((used)) static void clear_rdrand_cpuid_bit(struct cpuinfo_x86 *c)
{
	/*
	 * Saving of the MSR used to hide the RDRAND support during
	 * suspend/resume is done by arch/x86/power/cpu.c, which is
	 * dependent on CONFIG_PM_SLEEP.
	 */
	if (!IS_ENABLED(CONFIG_PM_SLEEP))
		return;

	/*
	 * The nordrand option can clear X86_FEATURE_RDRAND, so check for
	 * RDRAND support using the CPUID function directly.
	 */
	if (!(cpuid_ecx(1) & BIT(30)) || rdrand_force)
		return;

	msr_clear_bit(MSR_AMD64_CPUID_FN_1, 62);

	/*
	 * Verify that the CPUID change has occurred in case the kernel is
	 * running virtualized and the hypervisor doesn't support the MSR.
	 */
	if (cpuid_ecx(1) & BIT(30)) {
		pr_info_once("BIOS may not properly restore RDRAND after suspend, but hypervisor does not support hiding RDRAND via CPUID.\n");
		return;
	}

	clear_cpu_cap(c, X86_FEATURE_RDRAND);
	pr_info_once("BIOS may not properly restore RDRAND after suspend, hiding RDRAND via CPUID. Use rdrand=force to reenable.\n");
}