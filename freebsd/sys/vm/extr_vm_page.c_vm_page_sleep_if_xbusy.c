#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  TYPE_2__* vm_object_t ;
struct TYPE_10__ {scalar_t__ busy; } ;
struct TYPE_9__ {TYPE_2__* object; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int TRUE ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_WLOCKED (TYPE_2__*) ; 
 int /*<<< orphan*/  VM_OBJECT_WLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  vm_page_busy_sleep (TYPE_1__*,char const*,int) ; 
 int /*<<< orphan*/  vm_page_lock_assert (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_page_xbusied (TYPE_1__*) ; 

int
vm_page_sleep_if_xbusy(vm_page_t m, const char *msg)
{
	vm_object_t obj;

	vm_page_lock_assert(m, MA_NOTOWNED);
	VM_OBJECT_ASSERT_WLOCKED(m->object);

	/*
	 * The page-specific object must be cached because page
	 * identity can change during the sleep, causing the
	 * re-lock of a different object.
	 * It is assumed that a reference to the object is already
	 * held by the callers.
	 */
	obj = m->object;
	if (vm_page_xbusied(m) || (obj != NULL && obj->busy)) {
		vm_page_busy_sleep(m, msg, true);
		VM_OBJECT_WLOCK(obj);
		return (TRUE);
	}
	return (FALSE);
}