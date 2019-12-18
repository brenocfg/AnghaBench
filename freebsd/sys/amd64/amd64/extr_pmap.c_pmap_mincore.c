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
typedef  int pd_entry_t ;

/* Variables and functions */
 int MINCORE_INCORE ; 
 int MINCORE_MODIFIED ; 
 int MINCORE_MODIFIED_OTHER ; 
 int MINCORE_REFERENCED ; 
 int MINCORE_REFERENCED_OTHER ; 
 int MINCORE_SUPER ; 
 int PDRMASK ; 
 int PG_FRAME ; 
 int PG_MANAGED ; 
 int PG_PS ; 
 int PG_PS_FRAME ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int pmap_accessed_bit (int /*<<< orphan*/ ) ; 
 int pmap_modified_bit (int /*<<< orphan*/ ) ; 
 int* pmap_pde (int /*<<< orphan*/ ,int) ; 
 int* pmap_pde_to_pte (int*,int) ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 

int
pmap_mincore(pmap_t pmap, vm_offset_t addr, vm_paddr_t *pap)
{
	pd_entry_t *pdep;
	pt_entry_t pte, PG_A, PG_M, PG_RW, PG_V;
	vm_paddr_t pa;
	int val;

	PG_A = pmap_accessed_bit(pmap);
	PG_M = pmap_modified_bit(pmap);
	PG_V = pmap_valid_bit(pmap);
	PG_RW = pmap_rw_bit(pmap);

	PMAP_LOCK(pmap);
	pdep = pmap_pde(pmap, addr);
	if (pdep != NULL && (*pdep & PG_V)) {
		if (*pdep & PG_PS) {
			pte = *pdep;
			/* Compute the physical address of the 4KB page. */
			pa = ((*pdep & PG_PS_FRAME) | (addr & PDRMASK)) &
			    PG_FRAME;
			val = MINCORE_SUPER;
		} else {
			pte = *pmap_pde_to_pte(pdep, addr);
			pa = pte & PG_FRAME;
			val = 0;
		}
	} else {
		pte = 0;
		pa = 0;
		val = 0;
	}
	if ((pte & PG_V) != 0) {
		val |= MINCORE_INCORE;
		if ((pte & (PG_M | PG_RW)) == (PG_M | PG_RW))
			val |= MINCORE_MODIFIED | MINCORE_MODIFIED_OTHER;
		if ((pte & PG_A) != 0)
			val |= MINCORE_REFERENCED | MINCORE_REFERENCED_OTHER;
	}
	if ((val & (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER)) !=
	    (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER) &&
	    (pte & (PG_MANAGED | PG_V)) == (PG_MANAGED | PG_V)) {
		*pap = pa;
	}
	PMAP_UNLOCK(pmap);
	return (val);
}