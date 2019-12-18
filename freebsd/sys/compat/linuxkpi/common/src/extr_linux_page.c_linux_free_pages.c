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
typedef  scalar_t__ vm_page_t ;
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 scalar_t__ PMAP_HAS_DMAP ; 
 int /*<<< orphan*/  linux_free_kmem (scalar_t__,unsigned int) ; 
 scalar_t__ page_address (scalar_t__) ; 
 int /*<<< orphan*/  vm_page_free (scalar_t__) ; 
 scalar_t__ vm_page_unwire_noq (scalar_t__) ; 

void
linux_free_pages(vm_page_t page, unsigned int order)
{
	if (PMAP_HAS_DMAP) {
		unsigned long npages = 1UL << order;
		unsigned long x;

		for (x = 0; x != npages; x++) {
			vm_page_t pgo = page + x;

			if (vm_page_unwire_noq(pgo))
				vm_page_free(pgo);
		}
	} else {
		vm_offset_t vaddr;

		vaddr = (vm_offset_t)page_address(page);

		linux_free_kmem(vaddr, order);
	}
}