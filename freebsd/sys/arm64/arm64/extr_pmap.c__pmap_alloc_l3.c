#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
struct rwlock {int dummy; } ;
typedef  TYPE_2__* pmap_t ;
typedef  int pd_entry_t ;
struct TYPE_16__ {int* pm_l0; } ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 int ATTR_MASK ; 
 size_t L0_ENTRIES_SHIFT ; 
 int L0_TABLE ; 
 int L1_TABLE ; 
 int L2_TABLE ; 
 size_t Ln_ADDR_MASK ; 
 size_t Ln_ENTRIES_SHIFT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t NUL1E ; 
 size_t NUL2E ; 
 int PG_ZERO ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  RELEASE_PV_LIST_LOCK (struct rwlock**) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  dmb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ishst ; 
 int pmap_load (int*) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pmap_store (int*,int) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  vm_page_free_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
_pmap_alloc_l3(pmap_t pmap, vm_pindex_t ptepindex, struct rwlock **lockp)
{
	vm_page_t m, l1pg, l2pg;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);

	/*
	 * Allocate a page table page.
	 */
	if ((m = vm_page_alloc(NULL, ptepindex, VM_ALLOC_NOOBJ |
	    VM_ALLOC_WIRED | VM_ALLOC_ZERO)) == NULL) {
		if (lockp != NULL) {
			RELEASE_PV_LIST_LOCK(lockp);
			PMAP_UNLOCK(pmap);
			vm_wait(NULL);
			PMAP_LOCK(pmap);
		}

		/*
		 * Indicate the need to retry.  While waiting, the page table
		 * page may have been allocated.
		 */
		return (NULL);
	}
	if ((m->flags & PG_ZERO) == 0)
		pmap_zero_page(m);

	/*
	 * Because of AArch64's weak memory consistency model, we must have a
	 * barrier here to ensure that the stores for zeroing "m", whether by
	 * pmap_zero_page() or an earlier function, are visible before adding
	 * "m" to the page table.  Otherwise, a page table walk by another
	 * processor's MMU could see the mapping to "m" and a stale, non-zero
	 * PTE within "m".
	 */
	dmb(ishst);

	/*
	 * Map the pagetable page into the process address space, if
	 * it isn't already there.
	 */

	if (ptepindex >= (NUL2E + NUL1E)) {
		pd_entry_t *l0;
		vm_pindex_t l0index;

		l0index = ptepindex - (NUL2E + NUL1E);
		l0 = &pmap->pm_l0[l0index];
		pmap_store(l0, VM_PAGE_TO_PHYS(m) | L0_TABLE);
	} else if (ptepindex >= NUL2E) {
		vm_pindex_t l0index, l1index;
		pd_entry_t *l0, *l1;
		pd_entry_t tl0;

		l1index = ptepindex - NUL2E;
		l0index = l1index >> L0_ENTRIES_SHIFT;

		l0 = &pmap->pm_l0[l0index];
		tl0 = pmap_load(l0);
		if (tl0 == 0) {
			/* recurse for allocating page dir */
			if (_pmap_alloc_l3(pmap, NUL2E + NUL1E + l0index,
			    lockp) == NULL) {
				vm_page_unwire_noq(m);
				vm_page_free_zero(m);
				return (NULL);
			}
		} else {
			l1pg = PHYS_TO_VM_PAGE(tl0 & ~ATTR_MASK);
			l1pg->ref_count++;
		}

		l1 = (pd_entry_t *)PHYS_TO_DMAP(pmap_load(l0) & ~ATTR_MASK);
		l1 = &l1[ptepindex & Ln_ADDR_MASK];
		pmap_store(l1, VM_PAGE_TO_PHYS(m) | L1_TABLE);
	} else {
		vm_pindex_t l0index, l1index;
		pd_entry_t *l0, *l1, *l2;
		pd_entry_t tl0, tl1;

		l1index = ptepindex >> Ln_ENTRIES_SHIFT;
		l0index = l1index >> L0_ENTRIES_SHIFT;

		l0 = &pmap->pm_l0[l0index];
		tl0 = pmap_load(l0);
		if (tl0 == 0) {
			/* recurse for allocating page dir */
			if (_pmap_alloc_l3(pmap, NUL2E + l1index,
			    lockp) == NULL) {
				vm_page_unwire_noq(m);
				vm_page_free_zero(m);
				return (NULL);
			}
			tl0 = pmap_load(l0);
			l1 = (pd_entry_t *)PHYS_TO_DMAP(tl0 & ~ATTR_MASK);
			l1 = &l1[l1index & Ln_ADDR_MASK];
		} else {
			l1 = (pd_entry_t *)PHYS_TO_DMAP(tl0 & ~ATTR_MASK);
			l1 = &l1[l1index & Ln_ADDR_MASK];
			tl1 = pmap_load(l1);
			if (tl1 == 0) {
				/* recurse for allocating page dir */
				if (_pmap_alloc_l3(pmap, NUL2E + l1index,
				    lockp) == NULL) {
					vm_page_unwire_noq(m);
					vm_page_free_zero(m);
					return (NULL);
				}
			} else {
				l2pg = PHYS_TO_VM_PAGE(tl1 & ~ATTR_MASK);
				l2pg->ref_count++;
			}
		}

		l2 = (pd_entry_t *)PHYS_TO_DMAP(pmap_load(l1) & ~ATTR_MASK);
		l2 = &l2[ptepindex & Ln_ADDR_MASK];
		pmap_store(l2, VM_PAGE_TO_PHYS(m) | L2_TABLE);
	}

	pmap_resident_count_inc(pmap, 1);

	return (m);
}