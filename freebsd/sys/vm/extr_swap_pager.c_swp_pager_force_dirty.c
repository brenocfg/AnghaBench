#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_10__ {scalar_t__ queue; } ;

/* Variables and functions */
 scalar_t__ PQ_NONE ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  swap_pager_unswapped (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_wired (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_xunbusy (TYPE_1__*) ; 

__attribute__((used)) static void
swp_pager_force_dirty(vm_page_t m)
{

	vm_page_dirty(m);
#ifdef INVARIANTS
	vm_page_lock(m);
	if (!vm_page_wired(m) && m->queue == PQ_NONE)
		panic("page %p is neither wired nor queued", m);
	vm_page_unlock(m);
#endif
	vm_page_xunbusy(m);
	swap_pager_unswapped(m);
}