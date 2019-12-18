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
typedef  int vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int ATTR_MASK ; 
 int ATTR_SW_MANAGED ; 
 int /*<<< orphan*/  CACHED_MEMORY ; 
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int DMAP_TO_PHYS (scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int L1_BLOCK ; 
 scalar_t__ L1_OFFSET ; 
 scalar_t__ L1_SIZE ; 
 int L1_TABLE ; 
 int L2_BLOCK ; 
 scalar_t__ L2_SIZE ; 
 int L3_OFFSET ; 
 int Ln_ENTRIES ; 
 int /*<<< orphan*/  MA_OWNED ; 
 scalar_t__ PAGE_MASK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int /*<<< orphan*/  PMAP_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VM_ALLOC_INTERRUPT ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_WIRED ; 
 int VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 scalar_t__ kva_alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kva_free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kenter (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kremove (scalar_t__) ; 
 int pmap_load (int*) ; 
 int /*<<< orphan*/  pmap_update_entry (int /*<<< orphan*/ ,int*,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static pt_entry_t *
pmap_demote_l1(pmap_t pmap, pt_entry_t *l1, vm_offset_t va)
{
	pt_entry_t *l2, newl2, oldl1;
	vm_offset_t tmpl1;
	vm_paddr_t l2phys, phys;
	vm_page_t ml2;
	int i;

	PMAP_LOCK_ASSERT(pmap, MA_OWNED);
	oldl1 = pmap_load(l1);
	KASSERT((oldl1 & ATTR_DESCR_MASK) == L1_BLOCK,
	    ("pmap_demote_l1: Demoting a non-block entry"));
	KASSERT((va & L1_OFFSET) == 0,
	    ("pmap_demote_l1: Invalid virtual address %#lx", va));
	KASSERT((oldl1 & ATTR_SW_MANAGED) == 0,
	    ("pmap_demote_l1: Level 1 table shouldn't be managed"));

	tmpl1 = 0;
	if (va <= (vm_offset_t)l1 && va + L1_SIZE > (vm_offset_t)l1) {
		tmpl1 = kva_alloc(PAGE_SIZE);
		if (tmpl1 == 0)
			return (NULL);
	}

	if ((ml2 = vm_page_alloc(NULL, 0, VM_ALLOC_INTERRUPT |
	    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED)) == NULL) {
		CTR2(KTR_PMAP, "pmap_demote_l1: failure for va %#lx"
		    " in pmap %p", va, pmap);
		return (NULL);
	}

	l2phys = VM_PAGE_TO_PHYS(ml2);
	l2 = (pt_entry_t *)PHYS_TO_DMAP(l2phys);

	/* Address the range points at */
	phys = oldl1 & ~ATTR_MASK;
	/* The attributed from the old l1 table to be copied */
	newl2 = oldl1 & ATTR_MASK;

	/* Create the new entries */
	for (i = 0; i < Ln_ENTRIES; i++) {
		l2[i] = newl2 | phys;
		phys += L2_SIZE;
	}
	KASSERT(l2[0] == ((oldl1 & ~ATTR_DESCR_MASK) | L2_BLOCK),
	    ("Invalid l2 page (%lx != %lx)", l2[0],
	    (oldl1 & ~ATTR_DESCR_MASK) | L2_BLOCK));

	if (tmpl1 != 0) {
		pmap_kenter(tmpl1, PAGE_SIZE,
		    DMAP_TO_PHYS((vm_offset_t)l1) & ~L3_OFFSET, CACHED_MEMORY);
		l1 = (pt_entry_t *)(tmpl1 + ((vm_offset_t)l1 & PAGE_MASK));
	}

	pmap_update_entry(pmap, l1, l2phys | L1_TABLE, va, PAGE_SIZE);

	if (tmpl1 != 0) {
		pmap_kremove(tmpl1);
		kva_free(tmpl1, PAGE_SIZE);
	}

	return (l2);
}