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
 int /*<<< orphan*/ * pmap_l3 (int /*<<< orphan*/ ,scalar_t__) ; 

void
pmap_qremove(vm_offset_t sva, int count)
{
	pt_entry_t *l3;
	vm_offset_t va;

	KASSERT(sva >= VM_MIN_KERNEL_ADDRESS, ("usermode va %lx", sva));

	for (va = sva; count-- > 0; va += PAGE_SIZE) {
		l3 = pmap_l3(kernel_pmap, va);
		KASSERT(l3 != NULL, ("pmap_kremove: Invalid address"));
		pmap_clear(l3);
	}
	pmap_invalidate_range(kernel_pmap, sva, va);
}