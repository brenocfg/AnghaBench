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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 scalar_t__ AD_BITS_SUPPORTED (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  EPT_MEMORY_TYPE_WB (int /*<<< orphan*/ ) ; 
 scalar_t__ EPT_PDE_SUPERPAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EPT_PWL4 (int /*<<< orphan*/ ) ; 
 scalar_t__ EPT_SUPPORTS_EXEC_ONLY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVEPT_ALL_TYPES_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVEPT_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVVPID_ALL_TYPES_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INVVPID_SUPPORTED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSR_VMX_EPT_VPID_CAP ; 
 int PMAP_EMULATE_AD_BITS ; 
 int PMAP_NESTED_IPIMASK ; 
 int PMAP_PDE_SUPERPAGE ; 
 int PMAP_SUPPORTS_EXEC_ONLY ; 
 int /*<<< orphan*/  TUNABLE_INT_FETCH (char*,int*) ; 
 int ept_enable_ad_bits ; 
 int ept_pmap_flags ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ) ; 

int
ept_init(int ipinum)
{
	int use_hw_ad_bits, use_superpages, use_exec_only;
	uint64_t cap;

	cap = rdmsr(MSR_VMX_EPT_VPID_CAP);

	/*
	 * Verify that:
	 * - page walk length is 4 steps
	 * - extended page tables can be laid out in write-back memory
	 * - invvpid instruction with all possible types is supported
	 * - invept instruction with all possible types is supported
	 */
	if (!EPT_PWL4(cap) ||
	    !EPT_MEMORY_TYPE_WB(cap) ||
	    !INVVPID_SUPPORTED(cap) ||
	    !INVVPID_ALL_TYPES_SUPPORTED(cap) ||
	    !INVEPT_SUPPORTED(cap) ||
	    !INVEPT_ALL_TYPES_SUPPORTED(cap))
		return (EINVAL);

	ept_pmap_flags = ipinum & PMAP_NESTED_IPIMASK;

	use_superpages = 1;
	TUNABLE_INT_FETCH("hw.vmm.ept.use_superpages", &use_superpages);
	if (use_superpages && EPT_PDE_SUPERPAGE(cap))
		ept_pmap_flags |= PMAP_PDE_SUPERPAGE;	/* 2MB superpage */

	use_hw_ad_bits = 1;
	TUNABLE_INT_FETCH("hw.vmm.ept.use_hw_ad_bits", &use_hw_ad_bits);
	if (use_hw_ad_bits && AD_BITS_SUPPORTED(cap))
		ept_enable_ad_bits = 1;
	else
		ept_pmap_flags |= PMAP_EMULATE_AD_BITS;

	use_exec_only = 1;
	TUNABLE_INT_FETCH("hw.vmm.ept.use_exec_only", &use_exec_only);
	if (use_exec_only && EPT_SUPPORTS_EXEC_ONLY(cap))
		ept_pmap_flags |= PMAP_SUPPORTS_EXEC_ONLY;

	return (0);
}