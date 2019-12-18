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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/  Maxmem ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_DMAP (scalar_t__) ; 
 scalar_t__ ctob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmu_booke_kenter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static vm_offset_t
mmu_booke_map(mmu_t mmu, vm_offset_t *virt, vm_paddr_t pa_start,
    vm_paddr_t pa_end, int prot)
{
	vm_offset_t sva = *virt;
	vm_offset_t va = sva;

#ifdef __powerpc64__
	/* XXX: Handle memory not starting at 0x0. */
	if (pa_end < ctob(Maxmem))
		return (PHYS_TO_DMAP(pa_start));
#endif

	while (pa_start < pa_end) {
		mmu_booke_kenter(mmu, va, pa_start);
		va += PAGE_SIZE;
		pa_start += PAGE_SIZE;
	}
	*virt = va;

	return (sva);
}