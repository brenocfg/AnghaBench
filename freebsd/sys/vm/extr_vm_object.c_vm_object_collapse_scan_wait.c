#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_13__ {int /*<<< orphan*/  memq; struct TYPE_13__* backing_object; } ;
struct TYPE_12__ {TYPE_2__* object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int OBSC_COLLAPSE_NOWAIT ; 
 TYPE_1__* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WUNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_busy_sleep (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  vm_radix_wait () ; 

__attribute__((used)) static vm_page_t
vm_object_collapse_scan_wait(vm_object_t object, vm_page_t p, vm_page_t next,
    int op)
{
	vm_object_t backing_object;

	VM_OBJECT_ASSERT_WLOCKED(object);
	backing_object = object->backing_object;
	VM_OBJECT_ASSERT_WLOCKED(backing_object);

	KASSERT(p == NULL || p->object == object || p->object == backing_object,
	    ("invalid ownership %p %p %p", p, object, backing_object));
	if ((op & OBSC_COLLAPSE_NOWAIT) != 0)
		return (next);
	/* The page is only NULL when rename fails. */
	if (p == NULL) {
		vm_radix_wait();
	} else {
		if (p->object == object)
			VM_OBJECT_WUNLOCK(backing_object);
		else
			VM_OBJECT_WUNLOCK(object);
		vm_page_busy_sleep(p, "vmocol", false);
	}
	VM_OBJECT_WLOCK(object);
	VM_OBJECT_WLOCK(backing_object);
	return (TAILQ_FIRST(&backing_object->memq));
}