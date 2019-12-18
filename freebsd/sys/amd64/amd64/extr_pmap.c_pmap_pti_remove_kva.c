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
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_long ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ VM_MAXUSER_ADDRESS ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 int X86_PG_V ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int* pmap_pti_pte (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_pti_unwire_pte (int*,scalar_t__) ; 
 int /*<<< orphan*/  pte_clear (int*) ; 
 int /*<<< orphan*/  pti ; 
 int /*<<< orphan*/  pti_obj ; 
 scalar_t__ rounddown2 (scalar_t__,scalar_t__) ; 
 scalar_t__ roundup2 (scalar_t__,scalar_t__) ; 

void
pmap_pti_remove_kva(vm_offset_t sva, vm_offset_t eva)
{
	pt_entry_t *pte;
	vm_offset_t va;

	if (!pti)
		return;
	sva = rounddown2(sva, PAGE_SIZE);
	MPASS(sva > VM_MAXUSER_ADDRESS);
	eva = roundup2(eva, PAGE_SIZE);
	MPASS(sva < eva);
	VM_OBJECT_WLOCK(pti_obj);
	for (va = sva; va < eva; va += PAGE_SIZE) {
		pte = pmap_pti_pte(va, NULL);
		KASSERT((*pte & X86_PG_V) != 0,
		    ("invalid pte va %#lx pte %#lx pt %#lx", va,
		    (u_long)pte, *pte));
		pte_clear(pte);
		pmap_pti_unwire_pte(pte, va);
	}
	pmap_invalidate_range(kernel_pmap, sva, eva);
	VM_OBJECT_WUNLOCK(pti_obj);
}