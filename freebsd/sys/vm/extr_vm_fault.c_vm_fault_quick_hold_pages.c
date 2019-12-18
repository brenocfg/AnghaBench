#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  scalar_t__ vm_size_t ;
typedef  int vm_prot_t ;
typedef  TYPE_1__* vm_page_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  TYPE_2__* vm_map_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_15__ {int /*<<< orphan*/  pmap; } ;
struct TYPE_14__ {scalar_t__ dirty; } ;
struct TYPE_13__ {int td_pflags; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ KERN_SUCCESS ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  PQ_INACTIVE ; 
 int TDP_NOFAULTING ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VM_FAULT_NORMAL ; 
 scalar_t__ VM_PAGE_BITS_ALL ; 
 int VM_PROT_QUICK_NOFAULT ; 
 int VM_PROT_WRITE ; 
 int atop (scalar_t__) ; 
 TYPE_12__* curthread ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_1__* pmap_extract_and_hold (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ round_page (scalar_t__) ; 
 scalar_t__ trunc_page (scalar_t__) ; 
 scalar_t__ vm_fault (TYPE_2__*,scalar_t__,int,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ vm_map_max (TYPE_2__*) ; 
 scalar_t__ vm_map_min (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unwire (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
vm_fault_quick_hold_pages(vm_map_t map, vm_offset_t addr, vm_size_t len,
    vm_prot_t prot, vm_page_t *ma, int max_count)
{
	vm_offset_t end, va;
	vm_page_t *mp;
	int count;
	boolean_t pmap_failed;

	if (len == 0)
		return (0);
	end = round_page(addr + len);
	addr = trunc_page(addr);

	/*
	 * Check for illegal addresses.
	 */
	if (addr < vm_map_min(map) || addr > end || end > vm_map_max(map))
		return (-1);

	if (atop(end - addr) > max_count)
		panic("vm_fault_quick_hold_pages: count > max_count");
	count = atop(end - addr);

	/*
	 * Most likely, the physical pages are resident in the pmap, so it is
	 * faster to try pmap_extract_and_hold() first.
	 */
	pmap_failed = FALSE;
	for (mp = ma, va = addr; va < end; mp++, va += PAGE_SIZE) {
		*mp = pmap_extract_and_hold(map->pmap, va, prot);
		if (*mp == NULL)
			pmap_failed = TRUE;
		else if ((prot & VM_PROT_WRITE) != 0 &&
		    (*mp)->dirty != VM_PAGE_BITS_ALL) {
			/*
			 * Explicitly dirty the physical page.  Otherwise, the
			 * caller's changes may go unnoticed because they are
			 * performed through an unmanaged mapping or by a DMA
			 * operation.
			 *
			 * The object lock is not held here.
			 * See vm_page_clear_dirty_mask().
			 */
			vm_page_dirty(*mp);
		}
	}
	if (pmap_failed) {
		/*
		 * One or more pages could not be held by the pmap.  Either no
		 * page was mapped at the specified virtual address or that
		 * mapping had insufficient permissions.  Attempt to fault in
		 * and hold these pages.
		 *
		 * If vm_fault_disable_pagefaults() was called,
		 * i.e., TDP_NOFAULTING is set, we must not sleep nor
		 * acquire MD VM locks, which means we must not call
		 * vm_fault().  Some (out of tree) callers mark
		 * too wide a code area with vm_fault_disable_pagefaults()
		 * already, use the VM_PROT_QUICK_NOFAULT flag to request
		 * the proper behaviour explicitly.
		 */
		if ((prot & VM_PROT_QUICK_NOFAULT) != 0 &&
		    (curthread->td_pflags & TDP_NOFAULTING) != 0)
			goto error;
		for (mp = ma, va = addr; va < end; mp++, va += PAGE_SIZE)
			if (*mp == NULL && vm_fault(map, va, prot,
			    VM_FAULT_NORMAL, mp) != KERN_SUCCESS)
				goto error;
	}
	return (count);
error:	
	for (mp = ma; mp < ma + count; mp++)
		if (*mp != NULL)
			vm_page_unwire(*mp, PQ_INACTIVE);
	return (-1);
}