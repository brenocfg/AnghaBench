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
typedef  int vm_paddr_t ;
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int ATTR_DEFAULT ; 
 int ATTR_IDX (int) ; 
 int ATTR_UXN ; 
 int ATTR_XN ; 
 int DEVICE_MEMORY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L3_OFFSET ; 
 int L3_PAGE ; 
 int PAGE_MASK ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int,int) ; 
 int* pmap_l2_to_l3 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pmap_load_store (int*,int) ; 
 int /*<<< orphan*/ * pmap_pde (int /*<<< orphan*/ ,int,int*) ; 

void
pmap_kenter(vm_offset_t sva, vm_size_t size, vm_paddr_t pa, int mode)
{
	pd_entry_t *pde;
	pt_entry_t *pte, attr;
	vm_offset_t va;
	int lvl;

	KASSERT((pa & L3_OFFSET) == 0,
	   ("pmap_kenter: Invalid physical address"));
	KASSERT((sva & L3_OFFSET) == 0,
	   ("pmap_kenter: Invalid virtual address"));
	KASSERT((size & PAGE_MASK) == 0,
	    ("pmap_kenter: Mapping is not page-sized"));

	attr = ATTR_DEFAULT | ATTR_IDX(mode) | L3_PAGE;
	if (mode == DEVICE_MEMORY)
		attr |= ATTR_XN;
	else
		attr |= ATTR_UXN;

	va = sva;
	while (size != 0) {
		pde = pmap_pde(kernel_pmap, va, &lvl);
		KASSERT(pde != NULL,
		    ("pmap_kenter: Invalid page entry, va: 0x%lx", va));
		KASSERT(lvl == 2, ("pmap_kenter: Invalid level %d", lvl));

		pte = pmap_l2_to_l3(pde, va);
		pmap_load_store(pte, (pa & ~L3_OFFSET) | attr);

		va += PAGE_SIZE;
		pa += PAGE_SIZE;
		size -= PAGE_SIZE;
	}
	pmap_invalidate_range(kernel_pmap, sva, va);
}