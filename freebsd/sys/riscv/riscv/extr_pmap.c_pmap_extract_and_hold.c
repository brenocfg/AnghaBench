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
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PTE_TO_PHYS (int) ; 
 int PTE_W ; 
 int VM_PROT_WRITE ; 
 int* pmap_l3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmap_load (int*) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

vm_page_t
pmap_extract_and_hold(pmap_t pmap, vm_offset_t va, vm_prot_t prot)
{
	pt_entry_t *l3p, l3;
	vm_paddr_t phys;
	vm_page_t m;

	m = NULL;
	PMAP_LOCK(pmap);
	l3p = pmap_l3(pmap, va);
	if (l3p != NULL && (l3 = pmap_load(l3p)) != 0) {
		if ((l3 & PTE_W) != 0 || (prot & VM_PROT_WRITE) == 0) {
			phys = PTE_TO_PHYS(l3);
			m = PHYS_TO_VM_PAGE(phys);
			if (!vm_page_wire_mapped(m))
				m = NULL;
		}
	}
	PMAP_UNLOCK(pmap);
	return (m);
}