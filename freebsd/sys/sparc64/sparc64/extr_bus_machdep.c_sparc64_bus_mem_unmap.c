#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_1__* bus_space_tag_t ;
typedef  int /*<<< orphan*/  bus_space_handle_t ;
typedef  scalar_t__ bus_size_t ;
struct TYPE_3__ {int /*<<< orphan*/ * bst_cookie; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  kva_free (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  pmap_kremove_flags (scalar_t__) ; 
 scalar_t__ rman_get_virtual (int /*<<< orphan*/ *) ; 
 scalar_t__ round_page (scalar_t__) ; 
 int /*<<< orphan*/  tlb_range_demap (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 

int
sparc64_bus_mem_unmap(bus_space_tag_t tag, bus_space_handle_t handle,
    bus_size_t size)
{
	vm_offset_t sva;
	vm_offset_t va;
	vm_offset_t endva;

	if (tag->bst_cookie == NULL ||
	    (sva = (vm_offset_t)rman_get_virtual(tag->bst_cookie)) == 0)
		return (0);
	sva = trunc_page(sva);
	endva = sva + round_page(size);
	for (va = sva; va < endva; va += PAGE_SIZE)
		pmap_kremove_flags(va);
	tlb_range_demap(kernel_pmap, sva, sva + size - 1);
	kva_free(sva, size);
	return (0);
}