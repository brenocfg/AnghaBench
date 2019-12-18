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
typedef  int pd_entry_t ;

/* Variables and functions */
 int PDRMASK ; 
 int PG_FRAME ; 
 int PG_PS ; 
 int PG_PS_FRAME ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int) ; 
 int /*<<< orphan*/  PMAP_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (int /*<<< orphan*/ ) ; 
 int VM_PROT_WRITE ; 
 int* pmap_pde (int /*<<< orphan*/ ,int) ; 
 int* pmap_pde_to_pte (int*,int) ; 
 int pmap_rw_bit (int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

vm_page_t
pmap_extract_and_hold(pmap_t pmap, vm_offset_t va, vm_prot_t prot)
{
	pd_entry_t pde, *pdep;
	pt_entry_t pte, PG_RW, PG_V;
	vm_page_t m;

	m = NULL;
	PG_RW = pmap_rw_bit(pmap);
	PG_V = pmap_valid_bit(pmap);

	PMAP_LOCK(pmap);
	pdep = pmap_pde(pmap, va);
	if (pdep != NULL && (pde = *pdep)) {
		if (pde & PG_PS) {
			if ((pde & PG_RW) != 0 || (prot & VM_PROT_WRITE) == 0)
				m = PHYS_TO_VM_PAGE((pde & PG_PS_FRAME) |
				    (va & PDRMASK));
		} else {
			pte = *pmap_pde_to_pte(pdep, va);
			if ((pte & PG_V) != 0 &&
			    ((pte & PG_RW) != 0 || (prot & VM_PROT_WRITE) == 0))
				m = PHYS_TO_VM_PAGE(pte & PG_FRAME);
		}
		if (m != NULL && !vm_page_wire_mapped(m))
			m = NULL;
	}
	PMAP_UNLOCK(pmap);
	return (m);
}