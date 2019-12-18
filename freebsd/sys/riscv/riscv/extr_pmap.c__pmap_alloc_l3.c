#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vm_pindex_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
struct rwlock {int dummy; } ;
typedef  int pt_entry_t ;
typedef  int pn_t ;
typedef  TYPE_2__* pmap_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_17__ {int /*<<< orphan*/ * pm_l1; } ;
struct TYPE_16__ {int flags; int /*<<< orphan*/  ref_count; } ;

/* Variables and functions */
 size_t L1_SHIFT ; 
 size_t L2_SHIFT ; 
 size_t Ln_ADDR_MASK ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t NUL1E ; 
 int PAGE_SIZE ; 
 int PG_ZERO ; 
 scalar_t__ PHYS_TO_DMAP (int /*<<< orphan*/ ) ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (TYPE_2__*) ; 
 int PTE_PPN0_S ; 
 int /*<<< orphan*/  PTE_TO_PHYS (scalar_t__) ; 
 int PTE_V ; 
 int /*<<< orphan*/  RELEASE_PV_LIST_LOCK (struct rwlock**) ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int VM_PAGE_TO_PHYS (TYPE_1__*) ; 
 int /*<<< orphan*/  pmap_distribute_l1 (TYPE_2__*,size_t,int) ; 
 scalar_t__ pmap_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_resident_count_inc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  pmap_store (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 int /*<<< orphan*/  pvh_global_lock ; 
 int /*<<< orphan*/  rw_rlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_runlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  vm_page_free_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
_pmap_alloc_l3(pmap_t pmap, vm_pindex_t ptepindex, struct rwlock **lockp)
{
	vm_page_t m, /*pdppg, */pdpg;
	pt_entry_t entry;
	vm_paddr_t phys;
	pn_t pn;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);

	/*
	 * Allocate a page table page.
	 */
	if ((m = vm_page_alloc(NULL, ptepindex, VM_ALLOC_NOOBJ |
	    VM_ALLOC_WIRED | VM_ALLOC_ZERO)) == NULL) {
		if (lockp != NULL) {
			RELEASE_PV_LIST_LOCK(lockp);
			PMAP_UNLOCK(pmap);
			rw_runlock(&pvh_global_lock);
			vm_wait(NULL);
			rw_rlock(&pvh_global_lock);
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
	 * Map the pagetable page into the process address space, if
	 * it isn't already there.
	 */

	if (ptepindex >= NUL1E) {
		pd_entry_t *l1;
		vm_pindex_t l1index;

		l1index = ptepindex - NUL1E;
		l1 = &pmap->pm_l1[l1index];

		pn = (VM_PAGE_TO_PHYS(m) / PAGE_SIZE);
		entry = (PTE_V);
		entry |= (pn << PTE_PPN0_S);
		pmap_store(l1, entry);
		pmap_distribute_l1(pmap, l1index, entry);
	} else {
		vm_pindex_t l1index;
		pd_entry_t *l1, *l2;

		l1index = ptepindex >> (L1_SHIFT - L2_SHIFT);
		l1 = &pmap->pm_l1[l1index];
		if (pmap_load(l1) == 0) {
			/* recurse for allocating page dir */
			if (_pmap_alloc_l3(pmap, NUL1E + l1index,
			    lockp) == NULL) {
				vm_page_unwire_noq(m);
				vm_page_free_zero(m);
				return (NULL);
			}
		} else {
			phys = PTE_TO_PHYS(pmap_load(l1));
			pdpg = PHYS_TO_VM_PAGE(phys);
			pdpg->ref_count++;
		}

		phys = PTE_TO_PHYS(pmap_load(l1));
		l2 = (pd_entry_t *)PHYS_TO_DMAP(phys);
		l2 = &l2[ptepindex & Ln_ADDR_MASK];

		pn = (VM_PAGE_TO_PHYS(m) / PAGE_SIZE);
		entry = (PTE_V);
		entry |= (pn << PTE_PPN0_S);
		pmap_store(l2, entry);
	}

	pmap_resident_count_inc(pmap, 1);

	return (m);
}