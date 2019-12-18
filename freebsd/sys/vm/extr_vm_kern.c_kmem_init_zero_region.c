#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
struct TYPE_5__ {int flags; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 
 int PG_ZERO ; 
 int VM_ALLOC_NOOBJ ; 
 int VM_ALLOC_NORMAL ; 
 int VM_ALLOC_WIRED ; 
 int VM_ALLOC_ZERO ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 scalar_t__ ZERO_REGION_SIZE ; 
 int /*<<< orphan*/  kernel_pmap ; 
 scalar_t__ kva_alloc (scalar_t__) ; 
 int /*<<< orphan*/  pmap_protect (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_qenter (scalar_t__,TYPE_1__**,int) ; 
 int /*<<< orphan*/  pmap_zero_page (TYPE_1__*) ; 
 TYPE_1__* vm_page_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void const* zero_region ; 

void
kmem_init_zero_region(void)
{
	vm_offset_t addr, i;
	vm_page_t m;

	/*
	 * Map a single physical page of zeros to a larger virtual range.
	 * This requires less looping in places that want large amounts of
	 * zeros, while not using much more physical resources.
	 */
	addr = kva_alloc(ZERO_REGION_SIZE);
	m = vm_page_alloc(NULL, 0, VM_ALLOC_NORMAL |
	    VM_ALLOC_NOOBJ | VM_ALLOC_WIRED | VM_ALLOC_ZERO);
	if ((m->flags & PG_ZERO) == 0)
		pmap_zero_page(m);
	for (i = 0; i < ZERO_REGION_SIZE; i += PAGE_SIZE)
		pmap_qenter(addr + i, &m, 1);
	pmap_protect(kernel_pmap, addr, addr + ZERO_REGION_SIZE, VM_PROT_READ);

	zero_region = (const void *)addr;
}