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
 int /*<<< orphan*/  MSR_AMD64_BU_CFG2 ; 
 int /*<<< orphan*/  MSR_AMD64_MCx_MASK (int) ; 
 int /*<<< orphan*/  X86_BUG_AMD_TLB_MMATCH ; 
 int /*<<< orphan*/  amd_erratum_383 ; 
 struct cpuinfo_x86 boot_cpu_data ; 
 int /*<<< orphan*/  check_enable_amd_mmconf_dmi () ; 
 scalar_t__ cpu_has_amd_erratum (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fam10h_check_enable_mmcfg () ; 
 int /*<<< orphan*/  msr_clear_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msr_set_bit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_cpu_bug (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void init_amd_gh(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_MMCONF_FAM10H
	/* do this for boot cpu */
	if (c == &boot_cpu_data)
		check_enable_amd_mmconf_dmi();

	fam10h_check_enable_mmcfg();
#endif

	/*
	 * Disable GART TLB Walk Errors on Fam10h. We do this here because this
	 * is always needed when GART is enabled, even in a kernel which has no
	 * MCE support built in. BIOS should disable GartTlbWlk Errors already.
	 * If it doesn't, we do it here as suggested by the BKDG.
	 *
	 * Fixes: https://bugzilla.kernel.org/show_bug.cgi?id=33012
	 */
	msr_set_bit(MSR_AMD64_MCx_MASK(4), 10);

	/*
	 * On family 10h BIOS may not have properly enabled WC+ support, causing
	 * it to be converted to CD memtype. This may result in performance
	 * degradation for certain nested-paging guests. Prevent this conversion
	 * by clearing bit 24 in MSR_AMD64_BU_CFG2.
	 *
	 * NOTE: we want to use the _safe accessors so as not to #GP kvm
	 * guests on older kvm hosts.
	 */
	msr_clear_bit(MSR_AMD64_BU_CFG2, 24);

	if (cpu_has_amd_erratum(c, amd_erratum_383))
		set_cpu_bug(c, X86_BUG_AMD_TLB_MMATCH);
}