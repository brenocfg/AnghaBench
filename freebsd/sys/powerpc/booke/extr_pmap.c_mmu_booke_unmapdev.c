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
typedef  scalar_t__ vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int VM_MAX_KERNEL_ADDRESS ; 
 int VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  kva_free (int,scalar_t__) ; 
 scalar_t__ roundup (scalar_t__,int /*<<< orphan*/ ) ; 
 int trunc_page (int) ; 

__attribute__((used)) static void
mmu_booke_unmapdev(mmu_t mmu, vm_offset_t va, vm_size_t size)
{
#ifdef SUPPORTS_SHRINKING_TLB1
	vm_offset_t base, offset;

	/*
	 * Unmap only if this is inside kernel virtual space.
	 */
	if ((va >= VM_MIN_KERNEL_ADDRESS) && (va <= VM_MAX_KERNEL_ADDRESS)) {
		base = trunc_page(va);
		offset = va & PAGE_MASK;
		size = roundup(offset + size, PAGE_SIZE);
		kva_free(base, size);
	}
#endif
}