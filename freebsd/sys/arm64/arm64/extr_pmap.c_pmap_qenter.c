#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* vm_page_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;
struct TYPE_5__ {scalar_t__ pv_memattr; } ;
struct TYPE_6__ {TYPE_1__ md; } ;

/* Variables and functions */
 int ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ATTR_AP_RW ; 
 int ATTR_DEFAULT ; 
 int ATTR_IDX (scalar_t__) ; 
 int ATTR_UXN ; 
 int ATTR_XN ; 
 scalar_t__ DEVICE_MEMORY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int L3_PAGE ; 
 scalar_t__ L3_SIZE ; 
 int VM_PAGE_TO_PHYS (TYPE_2__*) ; 
 int /*<<< orphan*/  kernel_pmap ; 
 int /*<<< orphan*/  pmap_invalidate_range (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_l2_to_l3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_load_store (int*,int) ; 
 int /*<<< orphan*/ * pmap_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

void
pmap_qenter(vm_offset_t sva, vm_page_t *ma, int count)
{
	pd_entry_t *pde;
	pt_entry_t *pte, pa;
	vm_offset_t va;
	vm_page_t m;
	int i, lvl;

	va = sva;
	for (i = 0; i < count; i++) {
		pde = pmap_pde(kernel_pmap, va, &lvl);
		KASSERT(pde != NULL,
		    ("pmap_qenter: Invalid page entry, va: 0x%lx", va));
		KASSERT(lvl == 2,
		    ("pmap_qenter: Invalid level %d", lvl));

		m = ma[i];
		pa = VM_PAGE_TO_PHYS(m) | ATTR_DEFAULT | ATTR_AP(ATTR_AP_RW) |
		    ATTR_UXN | ATTR_IDX(m->md.pv_memattr) | L3_PAGE;
		if (m->md.pv_memattr == DEVICE_MEMORY)
			pa |= ATTR_XN;
		pte = pmap_l2_to_l3(pde, va);
		pmap_load_store(pte, pa);

		va += L3_SIZE;
	}
	pmap_invalidate_range(kernel_pmap, sva, va);
}