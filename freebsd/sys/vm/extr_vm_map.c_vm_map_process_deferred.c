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
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  TYPE_2__* vm_map_entry_t ;
struct thread {TYPE_2__* td_map_def_user; } ;
struct TYPE_5__ {int /*<<< orphan*/ * vm_object; } ;
struct TYPE_6__ {int eflags; int /*<<< orphan*/  end; int /*<<< orphan*/  start; TYPE_1__ object; struct TYPE_6__* defer_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int MAP_ENTRY_IS_SUB_MAP ; 
 int MAP_ENTRY_VN_EXEC ; 
 int MAP_ENTRY_WRITECNT ; 
 int /*<<< orphan*/  MPASS (int) ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  vm_map_entry_deallocate (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_map_entry_set_vnode_text (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vm_pager_release_writecount (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vm_map_process_deferred(void)
{
	struct thread *td;
	vm_map_entry_t entry, next;
	vm_object_t object;

	td = curthread;
	entry = td->td_map_def_user;
	td->td_map_def_user = NULL;
	while (entry != NULL) {
		next = entry->defer_next;
		MPASS((entry->eflags & (MAP_ENTRY_WRITECNT |
		    MAP_ENTRY_VN_EXEC)) != (MAP_ENTRY_WRITECNT |
		    MAP_ENTRY_VN_EXEC));
		if ((entry->eflags & MAP_ENTRY_WRITECNT) != 0) {
			/*
			 * Decrement the object's writemappings and
			 * possibly the vnode's v_writecount.
			 */
			KASSERT((entry->eflags & MAP_ENTRY_IS_SUB_MAP) == 0,
			    ("Submap with writecount"));
			object = entry->object.vm_object;
			KASSERT(object != NULL, ("No object for writecount"));
			vm_pager_release_writecount(object, entry->start,
			    entry->end);
		}
		vm_map_entry_set_vnode_text(entry, false);
		vm_map_entry_deallocate(entry, FALSE);
		entry = next;
	}
}