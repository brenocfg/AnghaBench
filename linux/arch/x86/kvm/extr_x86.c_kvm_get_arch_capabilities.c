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
typedef  int u64 ;

/* Variables and functions */
 int ARCH_CAP_MDS_NO ; 
 int ARCH_CAP_PSCHANGE_MC_NO ; 
 int ARCH_CAP_RDCL_NO ; 
 int ARCH_CAP_SKIP_VMENTRY_L1DFLUSH ; 
 int ARCH_CAP_SSB_NO ; 
 int ARCH_CAP_TSX_CTRL_MSR ; 
 int /*<<< orphan*/  MSR_IA32_ARCH_CAPABILITIES ; 
 scalar_t__ VMENTER_L1D_FLUSH_NEVER ; 
 int /*<<< orphan*/  X86_BUG_CPU_MELTDOWN ; 
 int /*<<< orphan*/  X86_BUG_MDS ; 
 int /*<<< orphan*/  X86_BUG_SPEC_STORE_BYPASS ; 
 int /*<<< orphan*/  X86_BUG_TAA ; 
 int /*<<< orphan*/  X86_FEATURE_ARCH_CAPABILITIES ; 
 int /*<<< orphan*/  X86_FEATURE_RTM ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ boot_cpu_has_bug (int /*<<< orphan*/ ) ; 
 scalar_t__ l1tf_vmx_mitigation ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static u64 kvm_get_arch_capabilities(void)
{
	u64 data = 0;

	if (boot_cpu_has(X86_FEATURE_ARCH_CAPABILITIES))
		rdmsrl(MSR_IA32_ARCH_CAPABILITIES, data);

	/*
	 * If nx_huge_pages is enabled, KVM's shadow paging will ensure that
	 * the nested hypervisor runs with NX huge pages.  If it is not,
	 * L1 is anyway vulnerable to ITLB_MULTIHIT explots from other
	 * L1 guests, so it need not worry about its own (L2) guests.
	 */
	data |= ARCH_CAP_PSCHANGE_MC_NO;

	/*
	 * If we're doing cache flushes (either "always" or "cond")
	 * we will do one whenever the guest does a vmlaunch/vmresume.
	 * If an outer hypervisor is doing the cache flush for us
	 * (VMENTER_L1D_FLUSH_NESTED_VM), we can safely pass that
	 * capability to the guest too, and if EPT is disabled we're not
	 * vulnerable.  Overall, only VMENTER_L1D_FLUSH_NEVER will
	 * require a nested hypervisor to do a flush of its own.
	 */
	if (l1tf_vmx_mitigation != VMENTER_L1D_FLUSH_NEVER)
		data |= ARCH_CAP_SKIP_VMENTRY_L1DFLUSH;

	if (!boot_cpu_has_bug(X86_BUG_CPU_MELTDOWN))
		data |= ARCH_CAP_RDCL_NO;
	if (!boot_cpu_has_bug(X86_BUG_SPEC_STORE_BYPASS))
		data |= ARCH_CAP_SSB_NO;
	if (!boot_cpu_has_bug(X86_BUG_MDS))
		data |= ARCH_CAP_MDS_NO;

	/*
	 * On TAA affected systems, export MDS_NO=0 when:
	 *	- TSX is enabled on the host, i.e. X86_FEATURE_RTM=1.
	 *	- Updated microcode is present. This is detected by
	 *	  the presence of ARCH_CAP_TSX_CTRL_MSR and ensures
	 *	  that VERW clears CPU buffers.
	 *
	 * When MDS_NO=0 is exported, guests deploy clear CPU buffer
	 * mitigation and don't complain:
	 *
	 *	"Vulnerable: Clear CPU buffers attempted, no microcode"
	 *
	 * If TSX is disabled on the system, guests are also mitigated against
	 * TAA and clear CPU buffer mitigation is not required for guests.
	 */
	if (boot_cpu_has_bug(X86_BUG_TAA) && boot_cpu_has(X86_FEATURE_RTM) &&
	    (data & ARCH_CAP_TSX_CTRL_MSR))
		data &= ~ARCH_CAP_MDS_NO;

	return data;
}