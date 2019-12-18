#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_object_t ;
struct TYPE_16__ {scalar_t__ type; int ref_count; int shadow_count; int flags; struct TYPE_16__* backing_object; int /*<<< orphan*/  paging_in_progress; int /*<<< orphan*/ * handle; int /*<<< orphan*/  shadow_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 TYPE_1__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ OBJT_DEFAULT ; 
 scalar_t__ OBJT_SWAP ; 
 scalar_t__ OBJT_VNODE ; 
 int OBJ_DEAD ; 
 int OBJ_ONEMAPPING ; 
 int OBJ_TMPFS_NODE ; 
 int /*<<< orphan*/  PVM ; 
 scalar_t__ REFCOUNT_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VM_OBJECT_RLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_RUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_TRYWLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  refcount_acquire (int*) ; 
 int /*<<< orphan*/  refcount_release (int*) ; 
 int refcount_release_if_gt (int*,int) ; 
 int /*<<< orphan*/  refcount_wait (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_list ; 
 int /*<<< orphan*/  umtx_shm_object_terminated (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_collapse (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_pip_wait (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  vm_object_set_flag (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_object_terminate (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_object_vndeallocate (TYPE_1__*) ; 

void
vm_object_deallocate(vm_object_t object)
{
	vm_object_t temp;
	bool released;

	while (object != NULL) {
		VM_OBJECT_RLOCK(object);
		if (object->type == OBJT_VNODE) {
			vm_object_vndeallocate(object);
			return;
		}

		/*
		 * If the reference count goes to 0 we start calling
		 * vm_object_terminate() on the object chain.  A ref count
		 * of 1 may be a special case depending on the shadow count
		 * being 0 or 1.  These cases require a write lock on the
		 * object.
		 */
		released = refcount_release_if_gt(&object->ref_count, 2);
		VM_OBJECT_RUNLOCK(object);
		if (released)
			return;

		VM_OBJECT_WLOCK(object);
		KASSERT(object->ref_count != 0,
			("vm_object_deallocate: object deallocated too many times: %d", object->type));

		refcount_release(&object->ref_count);
		if (object->ref_count > 1) {
			VM_OBJECT_WUNLOCK(object);
			return;
		} else if (object->ref_count == 1) {
			if (object->shadow_count == 0 &&
			    object->handle == NULL &&
			    (object->type == OBJT_DEFAULT ||
			    (object->type == OBJT_SWAP &&
			    (object->flags & OBJ_TMPFS_NODE) == 0))) {
				vm_object_set_flag(object, OBJ_ONEMAPPING);
			} else if ((object->shadow_count == 1) &&
			    (object->handle == NULL) &&
			    (object->type == OBJT_DEFAULT ||
			     object->type == OBJT_SWAP)) {
				vm_object_t robject;

				robject = LIST_FIRST(&object->shadow_head);
				KASSERT(robject != NULL,
				    ("vm_object_deallocate: ref_count: %d, shadow_count: %d",
					 object->ref_count,
					 object->shadow_count));
				KASSERT((robject->flags & OBJ_TMPFS_NODE) == 0,
				    ("shadowed tmpfs v_object %p", object));
				if (!VM_OBJECT_TRYWLOCK(robject)) {
					/*
					 * Avoid a potential deadlock.
					 */
					refcount_acquire(&object->ref_count);
					VM_OBJECT_WUNLOCK(object);
					/*
					 * More likely than not the thread
					 * holding robject's lock has lower
					 * priority than the current thread.
					 * Let the lower priority thread run.
					 */
					pause("vmo_de", 1);
					continue;
				}
				/*
				 * Collapse object into its shadow unless its
				 * shadow is dead.  In that case, object will
				 * be deallocated by the thread that is
				 * deallocating its shadow.
				 */
				if ((robject->flags & OBJ_DEAD) == 0 &&
				    (robject->handle == NULL) &&
				    (robject->type == OBJT_DEFAULT ||
				     robject->type == OBJT_SWAP)) {

					refcount_acquire(&robject->ref_count);
retry:
					if (REFCOUNT_COUNT(robject->paging_in_progress) > 0) {
						VM_OBJECT_WUNLOCK(object);
						vm_object_pip_wait(robject,
						    "objde1");
						temp = robject->backing_object;
						if (object == temp) {
							VM_OBJECT_WLOCK(object);
							goto retry;
						}
					} else if (REFCOUNT_COUNT(object->paging_in_progress) > 0) {
						VM_OBJECT_WUNLOCK(robject);
						VM_OBJECT_WUNLOCK(object);
						refcount_wait(
						    &object->paging_in_progress,
						    "objde2", PVM);
						VM_OBJECT_WLOCK(robject);
						temp = robject->backing_object;
						if (object == temp) {
							VM_OBJECT_WLOCK(object);
							goto retry;
						}
					} else
						VM_OBJECT_WUNLOCK(object);

					if (robject->ref_count == 1) {
						robject->ref_count--;
						object = robject;
						goto doterm;
					}
					object = robject;
					vm_object_collapse(object);
					VM_OBJECT_WUNLOCK(object);
					continue;
				}
				VM_OBJECT_WUNLOCK(robject);
			}
			VM_OBJECT_WUNLOCK(object);
			return;
		}
doterm:
		umtx_shm_object_terminated(object);
		temp = object->backing_object;
		if (temp != NULL) {
			KASSERT((object->flags & OBJ_TMPFS_NODE) == 0,
			    ("shadowed tmpfs v_object 2 %p", object));
			VM_OBJECT_WLOCK(temp);
			LIST_REMOVE(object, shadow_list);
			temp->shadow_count--;
			VM_OBJECT_WUNLOCK(temp);
			object->backing_object = NULL;
		}
		/*
		 * Don't double-terminate, we could be in a termination
		 * recursion due to the terminate having to sync data
		 * to disk.
		 */
		if ((object->flags & OBJ_DEAD) == 0) {
			vm_object_set_flag(object, OBJ_DEAD);
			vm_object_terminate(object);
		} else
			VM_OBJECT_WUNLOCK(object);
		object = temp;
	}
}