#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int vm_prot_t ;
typedef  scalar_t__ vm_pindex_t ;
typedef  TYPE_2__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_14__ {scalar_t__ clean_sva; scalar_t__ clean_eva; } ;
struct TYPE_12__ {int /*<<< orphan*/  pat_mode; } ;
struct TYPE_13__ {int oflags; scalar_t__ pindex; TYPE_1__ md; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PG_FRAME ; 
 int PG_MANAGED ; 
 int PG_PS ; 
 int PG_U ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 TYPE_2__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int VM_PROT_EXECUTE ; 
 int VPO_UNMANAGED ; 
 TYPE_2__* _pmap_allocpte (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 TYPE_8__ kmi ; 
 int pg_nx ; 
 int pmap_cache_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,scalar_t__) ; 
 int* pmap_pde (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pmap_pde_pindex (scalar_t__) ; 
 int pmap_pkru_get (int /*<<< orphan*/ ,scalar_t__) ; 
 size_t pmap_pte_index (scalar_t__) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_try_insert_pv_entry (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*,struct rwlock**) ; 
 scalar_t__ pmap_unwire_ptp (int /*<<< orphan*/ ,scalar_t__,TYPE_2__*,struct spglist*) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_store (int*,int) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 
 int* vtopte (scalar_t__) ; 

__attribute__((used)) static vm_page_t
pmap_enter_quick_locked(pmap_t pmap, vm_offset_t va, vm_page_t m,
    vm_prot_t prot, vm_page_t mpte, struct rwlock **lockp)
{
	struct spglist free;
	pt_entry_t newpte, *pte, PG_V;

	KASSERT(va < kmi.clean_sva || va >= kmi.clean_eva ||
	    (m->oflags & VPO_UNMANAGED) != 0,
	    ("pmap_enter_quick_locked: managed mapping within the clean submap"));
	PG_V = pmap_valid_bit(pmap);
	PMAP_LOCK_ASSERT(pmap, MA_OWNED);

	/*
	 * In the case that a page table page is not
	 * resident, we are creating it here.
	 */
	if (va < VM_MAXUSER_ADDRESS) {
		vm_pindex_t ptepindex;
		pd_entry_t *ptepa;

		/*
		 * Calculate pagetable page index
		 */
		ptepindex = pmap_pde_pindex(va);
		if (mpte && (mpte->pindex == ptepindex)) {
			mpte->ref_count++;
		} else {
			/*
			 * Get the page directory entry
			 */
			ptepa = pmap_pde(pmap, va);

			/*
			 * If the page table page is mapped, we just increment
			 * the hold count, and activate it.  Otherwise, we
			 * attempt to allocate a page table page.  If this
			 * attempt fails, we don't retry.  Instead, we give up.
			 */
			if (ptepa && (*ptepa & PG_V) != 0) {
				if (*ptepa & PG_PS)
					return (NULL);
				mpte = PHYS_TO_VM_PAGE(*ptepa & PG_FRAME);
				mpte->ref_count++;
			} else {
				/*
				 * Pass NULL instead of the PV list lock
				 * pointer, because we don't intend to sleep.
				 */
				mpte = _pmap_allocpte(pmap, ptepindex, NULL);
				if (mpte == NULL)
					return (mpte);
			}
		}
		pte = (pt_entry_t *)PHYS_TO_DMAP(VM_PAGE_TO_PHYS(mpte));
		pte = &pte[pmap_pte_index(va)];
	} else {
		mpte = NULL;
		pte = vtopte(va);
	}
	if (*pte) {
		if (mpte != NULL) {
			mpte->ref_count--;
			mpte = NULL;
		}
		return (mpte);
	}

	/*
	 * Enter on the PV list if part of our managed memory.
	 */
	if ((m->oflags & VPO_UNMANAGED) == 0 &&
	    !pmap_try_insert_pv_entry(pmap, va, m, lockp)) {
		if (mpte != NULL) {
			SLIST_INIT(&free);
			if (pmap_unwire_ptp(pmap, va, mpte, &free)) {
				/*
				 * Although "va" is not mapped, paging-
				 * structure caches could nonetheless have
				 * entries that refer to the freed page table
				 * pages.  Invalidate those entries.
				 */
				pmap_invalidate_page(pmap, va);
				vm_page_free_pages_toq(&free, true);
			}
			mpte = NULL;
		}
		return (mpte);
	}

	/*
	 * Increment counters
	 */
	pmap_resident_count_inc(pmap, 1);

	newpte = VM_PAGE_TO_PHYS(m) | PG_V |
	    pmap_cache_bits(pmap, m->md.pat_mode, 0);
	if ((m->oflags & VPO_UNMANAGED) == 0)
		newpte |= PG_MANAGED;
	if ((prot & VM_PROT_EXECUTE) == 0)
		newpte |= pg_nx;
	if (va < VM_MAXUSER_ADDRESS)
		newpte |= PG_U | pmap_pkru_get(pmap, va);
	pte_store(pte, newpte);
	return (mpte);
}