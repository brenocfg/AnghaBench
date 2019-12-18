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
typedef  scalar_t__ vm_paddr_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_memattr_t ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int PTE_C (int /*<<< orphan*/ ) ; 
 int PTE_D ; 
 int PTE_G ; 
 int PTE_V ; 
 int TLBLO_PA_TO_PFN (scalar_t__) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int* pmap_pte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pmap_update_page (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  printf (char*,void*,void*) ; 
 scalar_t__ pte_test (int*,int) ; 

void
pmap_kenter_attr(vm_offset_t va, vm_paddr_t pa, vm_memattr_t ma)
{
	pt_entry_t *pte;
	pt_entry_t opte, npte;

#ifdef PMAP_DEBUG
	printf("pmap_kenter:  va: %p -> pa: %p\n", (void *)va, (void *)pa);
#endif

	pte = pmap_pte(kernel_pmap, va);
	opte = *pte;
	npte = TLBLO_PA_TO_PFN(pa) | PTE_C(ma) | PTE_D | PTE_V | PTE_G;
	*pte = npte;
	if (pte_test(&opte, PTE_V) && opte != npte)
		pmap_update_page(kernel_pmap, va, npte);
}