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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int vm_offset_t ;

/* Variables and functions */
 scalar_t__ DEVMAP_PADDR_NOTFOUND ; 
 int PAGE_MASK ; 
 scalar_t__ devmap_vtop (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kva_free (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_kremove_device (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  round_page (int /*<<< orphan*/ ) ; 
 int trunc_page (int) ; 

void
pmap_unmapdev(vm_offset_t va, vm_size_t size)
{
	vm_offset_t offset;

	/* Nothing to do if we find the mapping in the static table. */
	if (devmap_vtop((void*)va, size) != DEVMAP_PADDR_NOTFOUND)
		return;

	offset = va & PAGE_MASK;
	va = trunc_page(va);
	size = round_page(size + offset);

	pmap_kremove_device(va, size);
	kva_free(va, size);
}