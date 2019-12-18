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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PHYS_TO_VM_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  pmap_inv_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kremove (int /*<<< orphan*/ ) ; 
 scalar_t__ vtophys (int /*<<< orphan*/ ) ; 

void
pmap_qremove(vm_offset_t va, int count)
{
	vm_paddr_t pa;
	int i;

	for (i = 0; i < count; i++) {
		pa = vtophys(va);
		if (pa) {
			pmap_inv_page(PHYS_TO_VM_PAGE(pa));
			pmap_kremove(va);
		}
		va += PAGE_SIZE;
	}
}