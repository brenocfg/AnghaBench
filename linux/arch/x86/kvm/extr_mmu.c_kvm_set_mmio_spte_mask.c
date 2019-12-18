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
typedef  unsigned long long u64 ;

/* Variables and functions */
 int ACC_USER_MASK ; 
 int ACC_WRITE_MASK ; 
 int /*<<< orphan*/  CONFIG_X86_64 ; 
 scalar_t__ IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_mmu_set_mmio_spte_mask (unsigned long long,unsigned long long,int) ; 
 int shadow_phys_bits ; 

__attribute__((used)) static void kvm_set_mmio_spte_mask(void)
{
	u64 mask;

	/*
	 * Set the reserved bits and the present bit of an paging-structure
	 * entry to generate page fault with PFER.RSV = 1.
	 */

	/*
	 * Mask the uppermost physical address bit, which would be reserved as
	 * long as the supported physical address width is less than 52.
	 */
	mask = 1ull << 51;

	/* Set the present bit. */
	mask |= 1ull;

	/*
	 * If reserved bit is not supported, clear the present bit to disable
	 * mmio page fault.
	 */
	if (IS_ENABLED(CONFIG_X86_64) && shadow_phys_bits == 52)
		mask &= ~1ull;

	kvm_mmu_set_mmio_spte_mask(mask, mask, ACC_WRITE_MASK | ACC_USER_MASK);
}