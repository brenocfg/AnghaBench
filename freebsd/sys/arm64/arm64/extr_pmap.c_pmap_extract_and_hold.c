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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_AP_RW ; 
 int ATTR_AP_RW_BIT ; 
 int ATTR_DESCR_MASK ; 
 int ATTR_MASK ; 
 int /*<<< orphan*/  CTASSERT (int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L1_BLOCK ; 
 int L1_OFFSET ; 
 int L2_BLOCK ; 
 int L2_OFFSET ; 
 int L3_PAGE ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int VM_PROT_WRITE ; 
 int pmap_load (int*) ; 
 int* pmap_pte (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

vm_page_t
pmap_extract_and_hold(pmap_t pmap, vm_offset_t va, vm_prot_t prot)
{
	pt_entry_t *pte, tpte;
	vm_offset_t off;
	vm_page_t m;
	int lvl;

	m = NULL;
	PMAP_LOCK(pmap);
	pte = pmap_pte(pmap, va, &lvl);
	if (pte != NULL) {
		tpte = pmap_load(pte);

		KASSERT(lvl > 0 && lvl <= 3,
		    ("pmap_extract_and_hold: Invalid level %d", lvl));
		CTASSERT(L1_BLOCK == L2_BLOCK);
		KASSERT((lvl == 3 && (tpte & ATTR_DESCR_MASK) == L3_PAGE) ||
		    (lvl < 3 && (tpte & ATTR_DESCR_MASK) == L1_BLOCK),
		    ("pmap_extract_and_hold: Invalid pte at L%d: %lx", lvl,
		     tpte & ATTR_DESCR_MASK));
		if (((tpte & ATTR_AP_RW_BIT) == ATTR_AP(ATTR_AP_RW)) ||
		    ((prot & VM_PROT_WRITE) == 0)) {
			switch(lvl) {
			case 1:
				off = va & L1_OFFSET;
				break;
			case 2:
				off = va & L2_OFFSET;
				break;
			case 3:
			default:
				off = 0;
			}
			m = PHYS_TO_VM_PAGE((tpte & ~ATTR_MASK) | off);
			if (!vm_page_wire_mapped(m))
				m = NULL;
		}
	}
	PMAP_UNLOCK(pmap);
	return (m);
}