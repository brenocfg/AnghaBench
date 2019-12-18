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
typedef  int vm_size_t ;
typedef  int vm_offset_t ;
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L3_OFFSET ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * pmap_l3 (int /*<<< orphan*/ ,int) ; 

void
pmap_kremove_device(vm_offset_t sva, vm_size_t size)
{
	pt_entry_t *l3;
	vm_offset_t va;

	KASSERT((sva & L3_OFFSET) == 0,
	   ("pmap_kremove_device: Invalid virtual address"));
	KASSERT((size & PAGE_MASK) == 0,
	    ("pmap_kremove_device: Mapping is not page-sized"));

	va = sva;
	while (size != 0) {
		l3 = pmap_l3(kernel_pmap, va);
		KASSERT(l3 != NULL, ("Invalid page table, va: 0x%lx", va));
		pmap_clear(l3);

		va += PAGE_SIZE;
		size -= PAGE_SIZE;
	}

	pmap_invalidate_range(kernel_pmap, sva, va);
}