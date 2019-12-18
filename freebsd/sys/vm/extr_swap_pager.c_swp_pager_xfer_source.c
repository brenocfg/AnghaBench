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
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  int /*<<< orphan*/  vm_object_t ;
typedef  scalar_t__ daddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SWAPBLK_NONE ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ swp_pager_meta_build (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ swp_pager_meta_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_object_pip_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vm_object_pip_wakeup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
swp_pager_xfer_source(vm_object_t srcobject, vm_object_t dstobject,
    vm_pindex_t pindex, daddr_t addr)
{
	daddr_t dstaddr;

	if (swp_pager_meta_ctl(dstobject, pindex, 0) != SWAPBLK_NONE) {
		/* Caller should destroy the source block. */
		return (false);
	}

	/*
	 * Destination has no swapblk and is not resident, transfer source.
	 * swp_pager_meta_build() can sleep.
	 */
	vm_object_pip_add(srcobject, 1);
	VM_OBJECT_WUNLOCK(srcobject);
	vm_object_pip_add(dstobject, 1);
	dstaddr = swp_pager_meta_build(dstobject, pindex, addr);
	KASSERT(dstaddr == SWAPBLK_NONE,
	    ("Unexpected destination swapblk"));
	vm_object_pip_wakeup(dstobject);
	VM_OBJECT_WLOCK(srcobject);
	vm_object_pip_wakeup(srcobject);
	return (true);
}