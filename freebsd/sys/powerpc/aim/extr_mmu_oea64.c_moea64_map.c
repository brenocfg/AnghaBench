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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 scalar_t__ LPTE_M ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (scalar_t__) ; 
 int /*<<< orphan*/  VM_MEMATTR_DEFAULT ; 
 scalar_t__ hw_direct_map ; 
 scalar_t__ moea64_calc_wimg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moea64_kenter (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

vm_offset_t
moea64_map(mmu_t mmu, vm_offset_t *virt, vm_paddr_t pa_start,
    vm_paddr_t pa_end, int prot)
{
	vm_offset_t	sva, va;

	if (hw_direct_map) {
		/*
		 * Check if every page in the region is covered by the direct
		 * map. The direct map covers all of physical memory. Use
		 * moea64_calc_wimg() as a shortcut to see if the page is in
		 * physical memory as a way to see if the direct map covers it.
		 */
		for (va = pa_start; va < pa_end; va += PAGE_SIZE)
			if (moea64_calc_wimg(va, VM_MEMATTR_DEFAULT) != LPTE_M)
				break;
		if (va == pa_end)
			return (PHYS_TO_DMAP(pa_start));
	}
	sva = *virt;
	va = sva;
	/* XXX respect prot argument */
	for (; pa_start < pa_end; pa_start += PAGE_SIZE, va += PAGE_SIZE)
		moea64_kenter(mmu, va, pa_start);
	*virt = va;

	return (sva);
}