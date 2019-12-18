#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
struct TYPE_3__ {int aflags; } ;

/* Variables and functions */
 int MINCORE_INCORE ; 
 int MINCORE_MODIFIED ; 
 int MINCORE_MODIFIED_OTHER ; 
 int MINCORE_REFERENCED ; 
 int MINCORE_REFERENCED_OTHER ; 
 int PGA_REFERENCED ; 
 TYPE_1__* PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_D ; 
 int /*<<< orphan*/  PTE_MANAGED ; 
 int /*<<< orphan*/  PTE_V ; 
 int /*<<< orphan*/  TLBLO_PTE_TO_PA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
pmap_mincore(pmap_t pmap, vm_offset_t addr, vm_paddr_t *pap)
{
	pt_entry_t *ptep, pte;
	vm_paddr_t pa;
	vm_page_t m;
	int val;

	PMAP_LOCK(pmap);
	ptep = pmap_pte(pmap, addr);
	pte = (ptep != NULL) ? *ptep : 0;
	if (!pte_test(&pte, PTE_V)) {
		PMAP_UNLOCK(pmap);
		return (0);
	}
	val = MINCORE_INCORE;
	if (pte_test(&pte, PTE_D))
		val |= MINCORE_MODIFIED | MINCORE_MODIFIED_OTHER;
	pa = TLBLO_PTE_TO_PA(pte);
	if (pte_test(&pte, PTE_MANAGED)) {
		/*
		 * This may falsely report the given address as
		 * MINCORE_REFERENCED.  Unfortunately, due to the lack of
		 * per-PTE reference information, it is impossible to
		 * determine if the address is MINCORE_REFERENCED.
		 */
		m = PHYS_TO_VM_PAGE(pa);
		if ((m->aflags & PGA_REFERENCED) != 0)
			val |= MINCORE_REFERENCED | MINCORE_REFERENCED_OTHER;
	}
	if ((val & (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER)) !=
	    (MINCORE_MODIFIED_OTHER | MINCORE_REFERENCED_OTHER) &&
	    pte_test(&pte, PTE_MANAGED)) {
		*pap = pa;
	}
	PMAP_UNLOCK(pmap);
	return (val);
}