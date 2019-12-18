#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_5__ {int /*<<< orphan*/  pv_flags; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 int MADV_DONTNEED ; 
 int MADV_FREE ; 
 int NBPDR ; 
 int NBSEG ; 
 scalar_t__ PAGE_SIZE ; 
 int PDRMASK ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE_D ; 
 int PTE_MANAGED ; 
 int PTE_V ; 
 int /*<<< orphan*/  PV_TABLE_REF ; 
 int SEGMASK ; 
 int /*<<< orphan*/  TLBLO_PTE_TO_PA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * pmap_pde_to_pte (scalar_t__*,int) ; 
 scalar_t__* pmap_pdpe_to_pde (scalar_t__*,int) ; 
 scalar_t__* pmap_segmap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pte_clear (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pte_test (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_2__*) ; 

void
pmap_advise(pmap_t pmap, vm_offset_t sva, vm_offset_t eva, int advice)
{
	pd_entry_t *pde, *pdpe;
	pt_entry_t *pte;
	vm_offset_t va, va_next;
	vm_paddr_t pa;
	vm_page_t m;

	if (advice != MADV_DONTNEED && advice != MADV_FREE)
		return;
	rw_wlock(&pvh_global_lock);
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
			if (!pte_test(pte, PTE_MANAGED | PTE_V)) {
				if (va != va_next) {
					pmap_invalidate_range(pmap, va, sva);
					va = va_next;
				}
				continue;
			}
			pa = TLBLO_PTE_TO_PA(*pte);
			m = PHYS_TO_VM_PAGE(pa);
			m->md.pv_flags &= ~PV_TABLE_REF;
			if (pte_test(pte, PTE_D)) {
				if (advice == MADV_DONTNEED) {
					/*
					 * Future calls to pmap_is_modified()
					 * can be avoided by making the page
					 * dirty now.
					 */
					vm_page_dirty(m);
				} else {
					pte_clear(pte, PTE_D);
					if (va == va_next)
						va = sva;
				}
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
		}
		if (va != va_next)
			pmap_invalidate_range(pmap, va, sva);
	}
	rw_wunlock(&pvh_global_lock);
	PMAP_UNLOCK(pmap);
}