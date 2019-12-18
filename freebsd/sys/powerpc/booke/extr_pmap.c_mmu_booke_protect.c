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
typedef  int vm_prot_t ;
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int pte_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ PTE_ISMANAGED (int*) ; 
 scalar_t__ PTE_ISMODIFIED (int*) ; 
 scalar_t__ PTE_ISVALID (int*) ; 
 int PTE_MODIFIED ; 
 int /*<<< orphan*/  PTE_PA (int*) ; 
 int PTE_SW ; 
 int PTE_UW ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  mmu_booke_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock_spin (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock_spin (int /*<<< orphan*/ *) ; 
 int* pte_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  tlb0_flush_entry (scalar_t__) ; 
 int /*<<< orphan*/  tlb_miss_lock () ; 
 int /*<<< orphan*/  tlb_miss_unlock () ; 
 int /*<<< orphan*/  tlbivax_mutex ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mmu_booke_protect(mmu_t mmu, pmap_t pmap, vm_offset_t sva, vm_offset_t eva,
    vm_prot_t prot)
{
	vm_offset_t va;
	vm_page_t m;
	pte_t *pte;

	if ((prot & VM_PROT_READ) == VM_PROT_NONE) {
		mmu_booke_remove(mmu, pmap, sva, eva);
		return;
	}

	if (prot & VM_PROT_WRITE)
		return;

	PMAP_LOCK(pmap);
	for (va = sva; va < eva; va += PAGE_SIZE) {
		if ((pte = pte_find(mmu, pmap, va)) != NULL) {
			if (PTE_ISVALID(pte)) {
				m = PHYS_TO_VM_PAGE(PTE_PA(pte));

				mtx_lock_spin(&tlbivax_mutex);
				tlb_miss_lock();

				/* Handle modified pages. */
				if (PTE_ISMODIFIED(pte) && PTE_ISMANAGED(pte))
					vm_page_dirty(m);

				tlb0_flush_entry(va);
				*pte &= ~(PTE_UW | PTE_SW | PTE_MODIFIED);

				tlb_miss_unlock();
				mtx_unlock_spin(&tlbivax_mutex);
			}
		}
	}
	PMAP_UNLOCK(pmap);
}