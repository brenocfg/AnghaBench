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
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
typedef  int u_int ;
struct TYPE_9__ {int oflags; int ref_count; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VM_OBJECT_TRYWLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (int /*<<< orphan*/ *) ; 
 int VPO_UNMANAGED ; 
 int VPRC_WIRE_COUNT (int) ; 
 int VPR_TRYFREE ; 
 scalar_t__ __predict_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_fcmpset_rel_int (int*,int*,int) ; 
 scalar_t__ atomic_load_ptr (int /*<<< orphan*/ **) ; 
 scalar_t__ vm_page_busied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_free (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_page_release_locked (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_release_toq (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_page_unlock (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_wire_sub (int) ; 

void
vm_page_release(vm_page_t m, int flags)
{
	vm_object_t object;
	u_int old;
	bool locked;

	KASSERT((m->oflags & VPO_UNMANAGED) == 0,
	    ("vm_page_release: page %p is unmanaged", m));

	if ((flags & VPR_TRYFREE) != 0) {
		for (;;) {
			object = (vm_object_t)atomic_load_ptr(&m->object);
			if (object == NULL)
				break;
			/* Depends on type-stability. */
			if (vm_page_busied(m) || !VM_OBJECT_TRYWLOCK(object)) {
				object = NULL;
				break;
			}
			if (object == m->object)
				break;
			VM_OBJECT_WUNLOCK(object);
		}
		if (__predict_true(object != NULL)) {
			vm_page_release_locked(m, flags);
			VM_OBJECT_WUNLOCK(object);
			return;
		}
	}

	/*
	 * Update LRU state before releasing the wiring reference.
	 * Use a release store when updating the reference count to
	 * synchronize with vm_page_free_prep().
	 */
	old = m->ref_count;
	locked = false;
	do {
		KASSERT(VPRC_WIRE_COUNT(old) > 0,
		    ("vm_page_unwire: wire count underflow for page %p", m));
		if (!locked && VPRC_WIRE_COUNT(old) == 1) {
			vm_page_lock(m);
			locked = true;
			vm_page_release_toq(m, flags);
		}
	} while (!atomic_fcmpset_rel_int(&m->ref_count, &old, old - 1));

	/*
	 * Release the lock only after the wiring is released, to ensure that
	 * the page daemon does not encounter and dequeue the page while it is
	 * still wired.
	 */
	if (locked)
		vm_page_unlock(m);

	if (VPRC_WIRE_COUNT(old) == 1) {
		vm_wire_sub(1);
		if (old == 1)
			vm_page_free(m);
	}
}