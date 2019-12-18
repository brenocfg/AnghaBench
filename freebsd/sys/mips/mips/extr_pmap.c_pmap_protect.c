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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ pd_entry_t ;

/* Variables and functions */
 int NBPDR ; 
 int NBSEG ; 
 scalar_t__ PAGE_SIZE ; 
 int PDRMASK ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_D ; 
 int /*<<< orphan*/  PTE_MANAGED ; 
 int /*<<< orphan*/  PTE_RO ; 
 int /*<<< orphan*/  PTE_V ; 
 int SEGMASK ; 
 int /*<<< orphan*/  TLBLO_PTE_TO_PA (int /*<<< orphan*/ ) ; 
 int VM_PROT_NONE ; 
 int VM_PROT_READ ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * pmap_pde_to_pte (scalar_t__*,int) ; 
 scalar_t__* pmap_pdpe_to_pde (scalar_t__*,int) ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__* pmap_segmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pte_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ ) ; 

void
pmap_protect(pmap_t pmap, vm_offset_t sva, vm_offset_t eva, vm_prot_t prot)
{
	pt_entry_t pbits, *pte;
	pd_entry_t *pde, *pdpe;
	vm_offset_t va, va_next;
	vm_paddr_t pa;
	vm_page_t m;

	if ((prot & VM_PROT_READ) == VM_PROT_NONE) {
		pmap_remove(pmap, sva, eva);
		return;
	}
	if (prot & VM_PROT_WRITE)
		return;

	PMAP_LOCK(pmap);
	for (; sva < eva; sva = va_next) {
		pdpe = pmap_segmap(pmap, sva);
#ifdef __mips_n64
		if (*pdpe == 0) {
			va_next = (sva + NBSEG) & ~SEGMASK;
			if (va_next < sva)
				va_next = eva;
			continue;
		}
#endif
		va_next = (sva + NBPDR) & ~PDRMASK;
		if (va_next < sva)
			va_next = eva;

		pde = pmap_pdpe_to_pde(pdpe, sva);
		if (*pde == NULL)
			continue;

		/*
		 * Limit our scan to either the end of the va represented
		 * by the current page table page, or to the end of the
		 * range being write protected.
		 */
		if (va_next > eva)
			va_next = eva;

		va = va_next;
		for (pte = pmap_pde_to_pte(pde, sva); sva != va_next; pte++,
		    sva += PAGE_SIZE) {
			pbits = *pte;
			if (!pte_test(&pbits, PTE_V) || pte_test(&pbits,
			    PTE_RO)) {
				if (va != va_next) {
					pmap_invalidate_range(pmap, va, sva);
					va = va_next;
				}
				continue;
			}
			pte_set(&pbits, PTE_RO);
			if (pte_test(&pbits, PTE_D)) {
				pte_clear(&pbits, PTE_D);
				if (pte_test(&pbits, PTE_MANAGED)) {
					pa = TLBLO_PTE_TO_PA(pbits);
					m = PHYS_TO_VM_PAGE(pa);
					vm_page_dirty(m);
				}
				if (va == va_next)
					va = sva;
			} else {
				/*
				 * Unless PTE_D is set, any TLB entries
				 * mapping "sva" don't allow write access, so
				 * they needn't be invalidated.
				 */
				if (va != va_next) {
					pmap_invalidate_range(pmap, va, sva);
					va = va_next;
				}
			}
			*pte = pbits;
		}
		if (va != va_next)
			pmap_invalidate_range(pmap, va, sva);
	}
	PMAP_UNLOCK(pmap);
}