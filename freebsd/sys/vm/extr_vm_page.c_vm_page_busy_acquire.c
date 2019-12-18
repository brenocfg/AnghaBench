#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/ * vm_object_t ;
struct TYPE_7__ {int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int TRUE ; 
 int VM_ALLOC_NOWAIT ; 
 int VM_ALLOC_SBUSY ; 
 int VM_ALLOC_WAITFAIL ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (int /*<<< orphan*/ *) ; 
 int VM_OBJECT_WOWNED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _vm_page_busy_sleep (int /*<<< orphan*/ *,TYPE_1__*,char*,int,int) ; 
 scalar_t__ vm_page_trysbusy (TYPE_1__*) ; 
 scalar_t__ vm_page_tryxbusy (TYPE_1__*) ; 
 scalar_t__ vm_page_wired (TYPE_1__*) ; 

int
vm_page_busy_acquire(vm_page_t m, int allocflags)
{
	vm_object_t obj;
	bool locked;

	/*
	 * The page-specific object must be cached because page
	 * identity can change during the sleep, causing the
	 * re-lock of a different object.
	 * It is assumed that a reference to the object is already
	 * held by the callers.
	 */
	obj = m->object;
	for (;;) {
		if ((allocflags & VM_ALLOC_SBUSY) == 0) {
			if (vm_page_tryxbusy(m))
				return (TRUE);
		} else {
			if (vm_page_trysbusy(m))
				return (TRUE);
		}
		if ((allocflags & VM_ALLOC_NOWAIT) != 0)
			return (FALSE);
		if (obj != NULL)
			locked = VM_OBJECT_WOWNED(obj);
		else
			locked = FALSE;
		MPASS(locked || vm_page_wired(m));
		_vm_page_busy_sleep(obj, m, "vmpba",
		    (allocflags & VM_ALLOC_SBUSY) != 0, locked);
		if (locked)
			VM_OBJECT_WLOCK(obj);
		if ((allocflags & VM_ALLOC_WAITFAIL) != 0)
			return (FALSE);
		KASSERT(m->object == obj || m->object == NULL,
		    ("vm_page_busy_acquire: page %p does not belong to %p",
		    m, obj));
	}
}