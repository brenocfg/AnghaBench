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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_AP_RO ; 
 int ATTR_DESCR_MASK ; 
 int ATTR_MASK ; 
 int ATTR_SW_MANAGED ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L2_BLOCK ; 
 int L2_OFFSET ; 
 size_t L2_SIZE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 size_t PAGE_SIZE ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fcmpset_64 (int*,int*,int) ; 
 int /*<<< orphan*/  pmap_invalidate_page (int /*<<< orphan*/ ,int) ; 
 int pmap_load (int*) ; 
 scalar_t__ pmap_pte_dirty (int) ; 
 int /*<<< orphan*/  vm_page_dirty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
pmap_protect_l2(pmap_t pmap, pt_entry_t *l2, vm_offset_t sva, pt_entry_t mask,
    pt_entry_t nbits)
{
	pd_entry_t old_l2;
	vm_page_t m, mt;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	KASSERT((sva & L2_OFFSET) == 0,
	    ("pmap_protect_l2: sva is not 2mpage aligned"));
	old_l2 = pmap_load(l2);
	KASSERT((old_l2 & ATTR_DESCR_MASK) == L2_BLOCK,
	    ("pmap_protect_l2: L2e %lx is not a block mapping", old_l2));

	/*
	 * Return if the L2 entry already has the desired access restrictions
	 * in place.
	 */
retry:
	if ((old_l2 & mask) == nbits)
		return;

	/*
	 * When a dirty read/write superpage mapping is write protected,
	 * update the dirty field of each of the superpage's constituent 4KB
	 * pages.
	 */
	if ((old_l2 & ATTR_SW_MANAGED) != 0 &&
	    (nbits & ATTR_AP(ATTR_AP_RO)) != 0 && pmap_pte_dirty(old_l2)) {
		m = PHYS_TO_VM_PAGE(old_l2 & ~ATTR_MASK);
		for (mt = m; mt < &m[L2_SIZE / PAGE_SIZE]; mt++)
			vm_page_dirty(mt);
	}

	if (!atomic_fcmpset_64(l2, &old_l2, (old_l2 & ~mask) | nbits))
		goto retry;

	/*
	 * Since a promotion must break the 4KB page mappings before making
	 * the 2MB page mapping, a pmap_invalidate_page() suffices.
	 */
	pmap_invalidate_page(pmap, sva);
}