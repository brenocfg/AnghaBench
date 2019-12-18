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
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int uint32_t ;
typedef  int pte_t ;
typedef  scalar_t__ pmap_t ;
typedef  int /*<<< orphan*/  mmu_t ;

/* Variables and functions */
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  PMAP_UNLOCK (scalar_t__) ; 
 scalar_t__ PTE_ISVALID (int*) ; 
 int /*<<< orphan*/  PTE_PA (int*) ; 
 int PTE_SW ; 
 int PTE_UW ; 
 int VM_PROT_WRITE ; 
 scalar_t__ kernel_pmap ; 
 int* pte_find (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_wire_mapped (int /*<<< orphan*/ *) ; 

__attribute__((used)) static vm_page_t
mmu_booke_extract_and_hold(mmu_t mmu, pmap_t pmap, vm_offset_t va,
    vm_prot_t prot)
{
	pte_t *pte;
	vm_page_t m;
	uint32_t pte_wbit;

	m = NULL;
	PMAP_LOCK(pmap);
	pte = pte_find(mmu, pmap, va);
	if ((pte != NULL) && PTE_ISVALID(pte)) {
		if (pmap == kernel_pmap)
			pte_wbit = PTE_SW;
		else
			pte_wbit = PTE_UW;

		if ((*pte & pte_wbit) != 0 || (prot & VM_PROT_WRITE) == 0) {
			m = PHYS_TO_VM_PAGE(PTE_PA(pte));
			if (!vm_page_wire_mapped(m))
				m = NULL;
		}
	}
	PMAP_UNLOCK(pmap);
	return (m);
}