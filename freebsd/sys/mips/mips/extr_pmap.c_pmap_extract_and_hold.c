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
typedef  int /*<<< orphan*/  vm_paddr_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_RO ; 
 int /*<<< orphan*/  PTE_V ; 
 int /*<<< orphan*/  TLBLO_PTE_TO_PA (int /*<<< orphan*/ ) ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pte_test (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

vm_page_t
pmap_extract_and_hold(pmap_t pmap, vm_offset_t va, vm_prot_t prot)
{
	pt_entry_t pte, *ptep;
	vm_paddr_t pa;
	vm_page_t m;

	m = NULL;
	PMAP_LOCK(pmap);
	ptep = pmap_pte(pmap, va);
	if (ptep != NULL) {
		pte = *ptep;
		if (pte_test(&pte, PTE_V) && (!pte_test(&pte, PTE_RO) ||
		    (prot & VM_PROT_WRITE) == 0)) {
			pa = TLBLO_PTE_TO_PA(pte);
			m = PHYS_TO_VM_PAGE(pa);
			if (!vm_page_wire_mapped(m))
				m = NULL;
		}
	}
	PMAP_UNLOCK(pmap);
	return (m);
}