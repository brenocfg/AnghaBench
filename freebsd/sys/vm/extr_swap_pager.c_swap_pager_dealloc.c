#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
struct TYPE_9__ {int flags; int /*<<< orphan*/  type; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  NOBJLIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJT_DEAD ; 
 int OBJ_DEAD ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_object_list ; 
 int /*<<< orphan*/  sw_alloc_sx ; 
 int /*<<< orphan*/  swp_pager_meta_free_all (TYPE_1__*) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_pip_wait (TYPE_1__*,char*) ; 

__attribute__((used)) static void
swap_pager_dealloc(vm_object_t object)
{

	VM_OBJECT_ASSERT_WLOCKED(object);
	KASSERT((object->flags & OBJ_DEAD) != 0, ("dealloc of reachable obj"));

	/*
	 * Remove from list right away so lookups will fail if we block for
	 * pageout completion.
	 */
	if (object->handle != NULL) {
		VM_OBJECT_WUNLOCK(object);
		sx_xlock(&sw_alloc_sx);
		TAILQ_REMOVE(NOBJLIST(object->handle), object,
		    pager_object_list);
		sx_xunlock(&sw_alloc_sx);
		VM_OBJECT_WLOCK(object);
	}

	vm_object_pip_wait(object, "swpdea");

	/*
	 * Free all remaining metadata.  We only bother to free it from
	 * the swap meta data.  We do not attempt to free swapblk's still
	 * associated with vm_page_t's for this object.  We do not care
	 * if paging is still in progress on some objects.
	 */
	swp_pager_meta_free_all(object);
	object->handle = NULL;
	object->type = OBJT_DEAD;
}