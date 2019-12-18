#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_8__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  PQ_INACTIVE ; 
 int VPR_NOREUSE ; 
 int VPR_TRYFREE ; 
 int /*<<< orphan*/  _vm_page_deactivate_noreuse (TYPE_1__*) ; 
 scalar_t__ vm_page_active (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_mvqueue (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_reference (TYPE_1__*) ; 

__attribute__((used)) static void
vm_page_release_toq(vm_page_t m, int flags)
{

	vm_page_assert_locked(m);

	/*
	 * Use a check of the valid bits to determine whether we should
	 * accelerate reclamation of the page.  The object lock might not be
	 * held here, in which case the check is racy.  At worst we will either
	 * accelerate reclamation of a valid page and violate LRU, or
	 * unnecessarily defer reclamation of an invalid page.
	 *
	 * If we were asked to not cache the page, place it near the head of the
	 * inactive queue so that is reclaimed sooner.
	 */
	if ((flags & (VPR_TRYFREE | VPR_NOREUSE)) != 0 || m->valid == 0)
		_vm_page_deactivate_noreuse(m);
	else if (vm_page_active(m))
		vm_page_reference(m);
	else
		vm_page_mvqueue(m, PQ_INACTIVE);
}