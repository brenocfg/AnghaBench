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
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int ATTR_DESCR_MASK ; 
 int ATTR_MASK ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L1_BLOCK ; 
 int L1_OFFSET ; 
 int L2_BLOCK ; 
 int L2_OFFSET ; 
 int L3_OFFSET ; 
 int L3_PAGE ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int pmap_load (int*) ; 
 int* pmap_pte (int /*<<< orphan*/ ,int,int*) ; 

vm_paddr_t
pmap_extract(pmap_t pmap, vm_offset_t va)
{
	pt_entry_t *pte, tpte;
	vm_paddr_t pa;
	int lvl;

	pa = 0;
	PMAP_LOCK(pmap);
	/*
	 * Find the block or page map for this virtual address. pmap_pte
	 * will return either a valid block/page entry, or NULL.
	 */
	pte = pmap_pte(pmap, va, &lvl);
	if (pte != NULL) {
		tpte = pmap_load(pte);
		pa = tpte & ~ATTR_MASK;
		switch(lvl) {
		case 1:
			KASSERT((tpte & ATTR_DESCR_MASK) == L1_BLOCK,
			    ("pmap_extract: Invalid L1 pte found: %lx",
			    tpte & ATTR_DESCR_MASK));
			pa |= (va & L1_OFFSET);
			break;
		case 2:
			KASSERT((tpte & ATTR_DESCR_MASK) == L2_BLOCK,
			    ("pmap_extract: Invalid L2 pte found: %lx",
			    tpte & ATTR_DESCR_MASK));
			pa |= (va & L2_OFFSET);
			break;
		case 3:
			KASSERT((tpte & ATTR_DESCR_MASK) == L3_PAGE,
			    ("pmap_extract: Invalid L3 pte found: %lx",
			    tpte & ATTR_DESCR_MASK));
			pa |= (va & L3_OFFSET);
			break;
		}
	}
	PMAP_UNLOCK(pmap);
	return (pa);
}