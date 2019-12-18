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
 int /*<<< orphan*/  VMX_EPT_MISCONFIG_WX_VALUE ; 
 int /*<<< orphan*/  VMX_EPT_RWX_MASK ; 
 int /*<<< orphan*/  kvm_mmu_set_mmio_spte_mask (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ept_set_mmio_spte_mask(void)
{
	/*
	 * EPT Misconfigurations can be generated if the value of bits 2:0
	 * of an EPT paging-structure entry is 110b (write/execute).
	 */
	kvm_mmu_set_mmio_spte_mask(VMX_EPT_RWX_MASK,
				   VMX_EPT_MISCONFIG_WX_VALUE, 0);
}