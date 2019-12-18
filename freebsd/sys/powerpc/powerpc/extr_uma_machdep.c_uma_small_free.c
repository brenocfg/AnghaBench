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
typedef  int /*<<< orphan*/ * vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  u_int8_t ;

/* Variables and functions */
 scalar_t__ DMAP_TO_PHYS (scalar_t__) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/ * PHYS_TO_VM_PAGE (scalar_t__) ; 
 int /*<<< orphan*/  VM_PAGE_TO_PHYS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_subtract_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dump_drop_page (int /*<<< orphan*/ ) ; 
 scalar_t__ hw_direct_map ; 
 int /*<<< orphan*/  hw_uma_mdpages ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_remove (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  vm_page_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_page_unwire_noq (int /*<<< orphan*/ *) ; 

void
uma_small_free(void *mem, vm_size_t size, u_int8_t flags)
{
	vm_page_t m;

	if (!hw_direct_map)
		pmap_remove(kernel_pmap,(vm_offset_t)mem,
		    (vm_offset_t)mem + PAGE_SIZE);

	if (hw_direct_map)
		m = PHYS_TO_VM_PAGE(DMAP_TO_PHYS((vm_offset_t)mem));
	else
		m = PHYS_TO_VM_PAGE((vm_offset_t)mem);
	KASSERT(m != NULL,
	    ("Freeing UMA block at %p with no associated page", mem));
#ifdef __powerpc64__
	dump_drop_page(VM_PAGE_TO_PHYS(m));
#endif
	vm_page_unwire_noq(m);
	vm_page_free(m);
	atomic_subtract_int(&hw_uma_mdpages, 1);
}