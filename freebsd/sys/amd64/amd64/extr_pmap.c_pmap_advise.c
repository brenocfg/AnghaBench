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
typedef  int /*<<< orphan*/  vm_page_t ;
typedef  int vm_offset_t ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int pml4_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pdp_entry_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MADV_DONTNEED ; 
 int MADV_FREE ; 
 int NBPDP ; 
 int NBPDR ; 
 int NBPML4 ; 
 scalar_t__ PAGE_SIZE ; 
 int PDPMASK ; 
 int PDRMASK ; 
 int PG_FRAME ; 
 int PG_MANAGED ; 
 int PG_PS ; 
 int PG_W ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PML4MASK ; 
 int /*<<< orphan*/  atomic_clear_long (int*,int) ; 
 int pmap_accessed_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_delayed_invl_finish () ; 
 int /*<<< orphan*/  pmap_delayed_invl_start () ; 
 int /*<<< orphan*/  pmap_demote_pde_locked (int /*<<< orphan*/ ,int*,int,struct rwlock**) ; 
 scalar_t__ pmap_emulate_ad_bits (int /*<<< orphan*/ ) ; 
 int pmap_global_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int,int) ; 
 int pmap_modified_bit (int /*<<< orphan*/ ) ; 
 int* pmap_pde_to_pte (int*,int) ; 
 int* pmap_pdpe_to_pde (int*,int) ; 
 int* pmap_pml4e (int /*<<< orphan*/ ,int) ; 
 int* pmap_pml4e_to_pdpe (int*,int) ; 
 int /*<<< orphan*/  pmap_remove_pte (int /*<<< orphan*/ ,int*,int,int,int /*<<< orphan*/ *,struct rwlock**) ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_wunlock (struct rwlock*) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ ) ; 

void
pmap_advise(pmap_t pmap, vm_offset_t sva, vm_offset_t eva, int advice)
{
	struct rwlock *lock;
	pml4_entry_t *pml4e;
	pdp_entry_t *pdpe;
	pd_entry_t oldpde, *pde;
	pt_entry_t *pte, PG_A, PG_G, PG_M, PG_RW, PG_V;
	vm_offset_t va, va_next;
	vm_page_t m;
	bool anychanged;

	if (advice != MADV_DONTNEED && advice != MADV_FREE)
		return;

	/*
	 * A/D bit emulation requires an alternate code path when clearing
	 * the modified and accessed bits below. Since this function is
	 * advisory in nature we skip it entirely for pmaps that require
	 * A/D bit emulation.
	 */
	if (pmap_emulate_ad_bits(pmap))
		return;

	PG_A = pmap_accessed_bit(pmap);
	PG_G = pmap_global_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_V = pmap_valid_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);
	anychanged = false;
	pmap_delayed_invl_start();
	PMAP_LOCK(pmap);
	for (; sva < eva; sva = va_next) {
		pml4e = pmap_pml4e(pmap, sva);
		if ((*pml4e & PG_V) == 0) {
			va_next = (sva + NBPML4) & ~PML4MASK;
			if (va_next < sva)
				va_next = eva;
			continue;
		}
		pdpe = pmap_pml4e_to_pdpe(pml4e, sva);
		if ((*pdpe & PG_V) == 0) {
			va_next = (sva + NBPDP) & ~PDPMASK;
			if (va_next < sva)
				va_next = eva;
			continue;
		}
		va_next = (sva + NBPDR) & ~PDRMASK;
		if (va_next < sva)
			va_next = eva;
		pde = pmap_pdpe_to_pde(pdpe, sva);
		oldpde = *pde;
		if ((oldpde & PG_V) == 0)
			continue;
		else if ((oldpde & PG_PS) != 0) {
			if ((oldpde & PG_MANAGED) == 0)
				continue;
			lock = NULL;
			if (!pmap_demote_pde_locked(pmap, pde, sva, &lock)) {
				if (lock != NULL)
					rw_wunlock(lock);

				/*
				 * The large page mapping was destroyed.
				 */
				continue;
			}

			/*
			 * Unless the page mappings are wired, remove the
			 * mapping to a single page so that a subsequent
			 * access may repromote.  Choosing the last page
			 * within the address range [sva, min(va_next, eva))
			 * generally results in more repromotions.  Since the
			 * underlying page table page is fully populated, this
			 * removal never frees a page table page.
			 */
			if ((oldpde & PG_W) == 0) {
				va = eva;
				if (va > va_next)
					va = va_next;
				va -= PAGE_SIZE;
				KASSERT(va >= sva,
				    ("pmap_advise: no address gap"));
				pte = pmap_pde_to_pte(pde, va);
				KASSERT((*pte & PG_V) != 0,
				    ("pmap_advise: invalid PTE"));
				pmap_remove_pte(pmap, pte, va, *pde, NULL,
				    &lock);
				anychanged = true;
			}
			if (lock != NULL)
				rw_wunlock(lock);
		}
		if (va_next > eva)
			va_next = eva;
		va = va_next;
		for (pte = pmap_pde_to_pte(pde, sva); sva != va_next; pte++,
		    sva += PAGE_SIZE) {
			if ((*pte & (PG_MANAGED | PG_V)) != (PG_MANAGED | PG_V))
				goto maybe_invlrng;
			else if ((*pte & (PG_M | PG_RW)) == (PG_M | PG_RW)) {
				if (advice == MADV_DONTNEED) {
					/*
					 * Future calls to pmap_is_modified()
					 * can be avoided by making the page
					 * dirty now.
					 */
					m = PHYS_TO_VM_PAGE(*pte & PG_FRAME);
					vm_page_dirty(m);
				}
				atomic_clear_long(pte, PG_M | PG_A);
			} else if ((*pte & PG_A) != 0)
				atomic_clear_long(pte, PG_A);
			else
				goto maybe_invlrng;

			if ((*pte & PG_G) != 0) {
				if (va == va_next)
					va = sva;
			} else
				anychanged = true;
			continue;
maybe_invlrng:
			if (va != va_next) {
				pmap_invalidate_range(pmap, va, sva);
				va = va_next;
			}
		}
		if (va != va_next)
			pmap_invalidate_range(pmap, va, sva);
	}
	if (anychanged)
		pmap_invalidate_all(pmap);
	PMAP_UNLOCK(pmap);
	pmap_delayed_invl_finish();
}