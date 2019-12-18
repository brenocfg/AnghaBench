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
typedef  int u_int ;
struct TYPE_7__ {int busy_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DROP_GIANT () ; 
 int /*<<< orphan*/  PICKUP_GIANT () ; 
 int /*<<< orphan*/  PVM ; 
 int /*<<< orphan*/  VM_OBJECT_DROP (int /*<<< orphan*/ *) ; 
 int VPB_BIT_SHARED ; 
 int VPB_BIT_WAITERS ; 
 int VPB_UNBUSIED ; 
 int /*<<< orphan*/  atomic_cmpset_int (int*,int,int) ; 
 int /*<<< orphan*/  sleepq_add (TYPE_1__*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleepq_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  sleepq_release (TYPE_1__*) ; 
 int /*<<< orphan*/  sleepq_wait (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_object_busied (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_object_busy_wait (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
_vm_page_busy_sleep(vm_object_t obj, vm_page_t m, const char *wmesg,
    bool nonshared, bool locked)
{
	u_int x;

	/*
	 * If the object is busy we must wait for that to drain to zero
	 * before trying the page again.
	 */
	if (obj != NULL && vm_object_busied(obj)) {
		if (locked)
			VM_OBJECT_DROP(obj);
		vm_object_busy_wait(obj, wmesg);
		return;
	}
	sleepq_lock(m);
	x = m->busy_lock;
	if (x == VPB_UNBUSIED || (nonshared && (x & VPB_BIT_SHARED) != 0) ||
	    ((x & VPB_BIT_WAITERS) == 0 &&
	    !atomic_cmpset_int(&m->busy_lock, x, x | VPB_BIT_WAITERS))) {
		if (locked)
			VM_OBJECT_DROP(obj);
		sleepq_release(m);
		return;
	}
	if (locked)
		VM_OBJECT_DROP(obj);
	DROP_GIANT();
	sleepq_add(m, NULL, wmesg, 0, 0);
	sleepq_wait(m, PVM);
	PICKUP_GIANT();
}