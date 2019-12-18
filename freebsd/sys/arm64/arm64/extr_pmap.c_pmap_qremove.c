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
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/ * pmap_pte (int /*<<< orphan*/ ,scalar_t__,int*) ; 

void
pmap_qremove(vm_offset_t sva, int count)
{
	pt_entry_t *pte;
	vm_offset_t va;
	int lvl;

	KASSERT(sva >= VM_MIN_KERNEL_ADDRESS, ("usermode va %lx", sva));

	va = sva;
	while (count-- > 0) {
		pte = pmap_pte(kernel_pmap, va, &lvl);
		KASSERT(lvl == 3,
		    ("Invalid device pagetable level: %d != 3", lvl));
		if (pte != NULL) {
			pmap_clear(pte);
		}

		va += PAGE_SIZE;
	}
	pmap_invalidate_range(kernel_pmap, sva, va);
}