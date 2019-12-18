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
 int L2_OFFSET ; 
 int L3_OFFSET ; 
 int MINCORE_INCORE ; 
 int MINCORE_MODIFIED ; 
 int MINCORE_MODIFIED_OTHER ; 
 int MINCORE_REFERENCED ; 
 int MINCORE_REFERENCED_OTHER ; 
 int MINCORE_SUPER ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE_A ; 
 int PTE_D ; 
 int PTE_RWX ; 
 int PTE_SW_MANAGED ; 
 int PTE_TO_PHYS (int) ; 
 int PTE_V ; 
 int* pmap_l2 (int /*<<< orphan*/ ,int) ; 
 int* pmap_l2_to_l3 (int*,int) ; 
 int pmap_load (int*) ; 

int
pmap_mincore(pmap_t pmap, vm_offset_t addr, vm_paddr_t *pap)
{
	pt_entry_t *l2, *l3, tpte;
	vm_paddr_t pa;
	int val;
	bool managed;

	PMAP_LOCK(pmap);
	l2 = pmap_l2(pmap, addr);
	if (l2 != NULL && ((tpte = pmap_load(l2)) & PTE_V) != 0) {
		if ((tpte & PTE_RWX) != 0) {
			pa = PTE_TO_PHYS(tpte) | (addr & L2_OFFSET);
			val = MINCORE_INCORE | MINCORE_SUPER;
		} else {
			l3 = pmap_l2_to_l3(l2, addr);
			tpte = pmap_load(l3);
			if ((tpte & PTE_V) == 0) {
				PMAP_UNLOCK(pmap);
				return (0);
			}
			pa = PTE_TO_PHYS(tpte) | (addr & L3_OFFSET);
			val = MINCORE_INCORE;
		}

		if ((tpte & PTE_D) != 0)
			val |= MINCORE_MODIFIED | MINCORE_MODIFIED_OTHER;
		if ((tpte & PTE_A) != 0)
			val |= MINCORE_REFERENCED | MINCORE_REFERENCED_OTHER;
		managed = (tpte & PTE_SW_MANAGED) == PTE_SW_MANAGED;
	} else {
		managed = false;
		val = 0;
	}
	if ((val & (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER)) !=
	    (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER) && managed) {
		*pap = pa;
	}
	PMAP_UNLOCK(pmap);
	return (val);
}