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
 unsigned long long VMX_EPT_ACCESS_BIT ; 
 unsigned long long VMX_EPT_DIRTY_BIT ; 
 int /*<<< orphan*/  VMX_EPT_EXECUTABLE_MASK ; 
 unsigned long long VMX_EPT_READABLE_MASK ; 
 int /*<<< orphan*/  VMX_EPT_RWX_MASK ; 
 scalar_t__ cpu_has_vmx_ept_execute_only () ; 
 scalar_t__ enable_ept_ad_bits ; 
 int /*<<< orphan*/  ept_set_mmio_spte_mask () ; 
 int /*<<< orphan*/  kvm_enable_tdp () ; 
 int /*<<< orphan*/  kvm_mmu_set_mask_ptes (unsigned long long,unsigned long long,unsigned long long,unsigned long long,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,unsigned long long) ; 

__attribute__((used)) static void vmx_enable_tdp(void)
{
	kvm_mmu_set_mask_ptes(VMX_EPT_READABLE_MASK,
		enable_ept_ad_bits ? VMX_EPT_ACCESS_BIT : 0ull,
		enable_ept_ad_bits ? VMX_EPT_DIRTY_BIT : 0ull,
		0ull, VMX_EPT_EXECUTABLE_MASK,
		cpu_has_vmx_ept_execute_only() ? 0ull : VMX_EPT_READABLE_MASK,
		VMX_EPT_RWX_MASK, 0ull);

	ept_set_mmio_spte_mask();
	kvm_enable_tdp();
}