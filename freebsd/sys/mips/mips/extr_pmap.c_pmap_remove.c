#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  TYPE_2__* pmap_t ;
typedef  scalar_t__ pd_entry_t ;
struct TYPE_10__ {scalar_t__ resident_count; } ;
struct TYPE_11__ {TYPE_1__ pm_stats; } ;

/* Variables and functions */
 int NBPDR ; 
 int NBSEG ; 
 int PAGE_SIZE ; 
 int PDRMASK ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PTE_V ; 
 int SEGMASK ; 
 int /*<<< orphan*/  pmap_invalidate_range (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/ * pmap_pde_to_pte (scalar_t__*,int) ; 
 scalar_t__* pmap_pdpe_to_pde (scalar_t__*,int) ; 
 int /*<<< orphan*/  pmap_remove_page (TYPE_2__*,int) ; 
 scalar_t__ pmap_remove_pte (TYPE_2__*,int /*<<< orphan*/ *,int,scalar_t__) ; 
 scalar_t__* pmap_segmap (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pte_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 

void
pmap_remove(pmap_t pmap, vm_offset_t sva, vm_offset_t eva)
{
	pd_entry_t *pde, *pdpe;
	pt_entry_t *pte;
	vm_offset_t va, va_next;

	/*
	 * Perform an unsynchronized read.  This is, however, safe.
	 */
	if (pmap->pm_stats.resident_count == 0)
		return;

	rw_wlock(&pvh_global_lock);
	PMAP_LOCK(pmap);

	/*
	 * special handling of removing one page.  a very common operation
	 * and easy to short circuit some code.
	 */
	if ((sva + PAGE_SIZE) == eva) {
		pmap_remove_page(pmap, sva);
		goto out;
	}
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
		 * range being removed.
		 */
		if (va_next > eva)
			va_next = eva;

		va = va_next;
		for (pte = pmap_pde_to_pte(pde, sva); sva != va_next; pte++,
		    sva += PAGE_SIZE) {
			if (!pte_test(pte, PTE_V)) {
				if (va != va_next) {
					pmap_invalidate_range(pmap, va, sva);
					va = va_next;
				}
				continue;
			}
			if (va == va_next)
				va = sva;
			if (pmap_remove_pte(pmap, pte, sva, *pde)) {
				sva += PAGE_SIZE;
				break;
			}
		}
		if (va != va_next)
			pmap_invalidate_range(pmap, va, sva);
	}
out:
	rw_wunlock(&pvh_global_lock);
	PMAP_UNLOCK(pmap);
}