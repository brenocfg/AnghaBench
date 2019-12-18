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
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int pt2_entry_t ;
typedef  int pt1_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int PTE1_OFFSET ; 
 int PTE1_RO ; 
 int PTE2_RO ; 
 int VM_PROT_WRITE ; 
 int /*<<< orphan*/  pmap_pte1 (int /*<<< orphan*/ ,int) ; 
 int* pmap_pte2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_pte2_release (int*) ; 
 scalar_t__ pte1_is_link (int) ; 
 scalar_t__ pte1_is_section (int) ; 
 int pte1_load (int /*<<< orphan*/ ) ; 
 int pte1_pa (int) ; 
 scalar_t__ pte2_is_valid (int) ; 
 int pte2_load (int*) ; 
 int pte2_pa (int) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

vm_page_t
pmap_extract_and_hold(pmap_t pmap, vm_offset_t va, vm_prot_t prot)
{
	vm_paddr_t pa;
	pt1_entry_t pte1;
	pt2_entry_t pte2, *pte2p;
	vm_page_t m;

	m = NULL;
	PMAP_LOCK(pmap);
	pte1 = pte1_load(pmap_pte1(pmap, va));
	if (pte1_is_section(pte1)) {
		if (!(pte1 & PTE1_RO) || !(prot & VM_PROT_WRITE)) {
			pa = pte1_pa(pte1) | (va & PTE1_OFFSET);
			m = PHYS_TO_VM_PAGE(pa);
			if (!vm_page_wire_mapped(m))
				m = NULL;
		}
	} else if (pte1_is_link(pte1)) {
		pte2p = pmap_pte2(pmap, va);
		pte2 = pte2_load(pte2p);
		pmap_pte2_release(pte2p);
		if (pte2_is_valid(pte2) &&
		    (!(pte2 & PTE2_RO) || !(prot & VM_PROT_WRITE))) {
			pa = pte2_pa(pte2);
			m = PHYS_TO_VM_PAGE(pa);
			if (!vm_page_wire_mapped(m))
				m = NULL;
		}
	}
	PMAP_UNLOCK(pmap);
	return (m);
}