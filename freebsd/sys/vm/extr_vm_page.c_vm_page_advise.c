#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
struct TYPE_12__ {scalar_t__ dirty; int /*<<< orphan*/  object; } ;

/* Variables and functions */
 int MADV_DONTNEED ; 
 int MADV_FREE ; 
 int MADV_WILLNEED ; 
 int /*<<< orphan*/  PGA_REFERENCED ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (int /*<<< orphan*/ ) ; 
 scalar_t__ pmap_is_modified (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_activate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_aflag_clear (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_assert_locked (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_deactivate_noreuse (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_in_laundry (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_launder (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_undirty (TYPE_1__*) ; 

void
vm_page_advise(vm_page_t m, int advice)
{

	vm_page_assert_locked(m);
	VM_OBJECT_ASSERT_WLOCKED(m->object);
	if (advice == MADV_FREE)
		/*
		 * Mark the page clean.  This will allow the page to be freed
		 * without first paging it out.  MADV_FREE pages are often
		 * quickly reused by malloc(3), so we do not do anything that
		 * would result in a page fault on a later access.
		 */
		vm_page_undirty(m);
	else if (advice != MADV_DONTNEED) {
		if (advice == MADV_WILLNEED)
			vm_page_activate(m);
		return;
	}

	/*
	 * Clear any references to the page.  Otherwise, the page daemon will
	 * immediately reactivate the page.
	 */
	vm_page_aflag_clear(m, PGA_REFERENCED);

	if (advice != MADV_FREE && m->dirty == 0 && pmap_is_modified(m))
		vm_page_dirty(m);

	/*
	 * Place clean pages near the head of the inactive queue rather than
	 * the tail, thus defeating the queue's LRU operation and ensuring that
	 * the page will be reused quickly.  Dirty pages not already in the
	 * laundry are moved there.
	 */
	if (m->dirty == 0)
		vm_page_deactivate_noreuse(m);
	else if (!vm_page_in_laundry(m))
		vm_page_launder(m);
}