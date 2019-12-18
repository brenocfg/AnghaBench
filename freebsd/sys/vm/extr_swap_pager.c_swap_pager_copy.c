#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vm_pindex_t ;
typedef  TYPE_1__* vm_object_t ;
struct TYPE_13__ {int /*<<< orphan*/  type; int /*<<< orphan*/  size; int /*<<< orphan*/ * handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOBJLIST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OBJT_DEFAULT ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_object_list ; 
 int /*<<< orphan*/  sw_alloc_sx ; 
 int /*<<< orphan*/  swp_pager_meta_free_all (TYPE_1__*) ; 
 int /*<<< orphan*/  swp_pager_meta_transfer (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_pip_add (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_object_pip_wakeup (TYPE_1__*) ; 

void
swap_pager_copy(vm_object_t srcobject, vm_object_t dstobject,
    vm_pindex_t offset, int destroysource)
{

	VM_OBJECT_ASSERT_WLOCKED(srcobject);
	VM_OBJECT_ASSERT_WLOCKED(dstobject);

	/*
	 * If destroysource is set, we remove the source object from the
	 * swap_pager internal queue now.
	 */
	if (destroysource && srcobject->handle != NULL) {
		vm_object_pip_add(srcobject, 1);
		VM_OBJECT_WUNLOCK(srcobject);
		vm_object_pip_add(dstobject, 1);
		VM_OBJECT_WUNLOCK(dstobject);
		sx_xlock(&sw_alloc_sx);
		TAILQ_REMOVE(NOBJLIST(srcobject->handle), srcobject,
		    pager_object_list);
		sx_xunlock(&sw_alloc_sx);
		VM_OBJECT_WLOCK(dstobject);
		vm_object_pip_wakeup(dstobject);
		VM_OBJECT_WLOCK(srcobject);
		vm_object_pip_wakeup(srcobject);
	}

	/*
	 * Transfer source to destination.
	 */
	swp_pager_meta_transfer(srcobject, dstobject, offset, dstobject->size);

	/*
	 * Free left over swap blocks in source.
	 *
	 * We have to revert the type to OBJT_DEFAULT so we do not accidentally
	 * double-remove the object from the swap queues.
	 */
	if (destroysource) {
		swp_pager_meta_free_all(srcobject);
		/*
		 * Reverting the type is not necessary, the caller is going
		 * to destroy srcobject directly, but I'm doing it here
		 * for consistency since we've removed the object from its
		 * queues.
		 */
		srcobject->type = OBJT_DEFAULT;
	}
}