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
typedef  int u_int ;
typedef  int /*<<< orphan*/  op ;
struct TYPE_7__ {int oflags; int ref_count; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VM_OBJECT_WOWNED (int /*<<< orphan*/ *) ; 
 int VPO_UNMANAGED ; 
 int VPRC_BLOCKED ; 
 int VPRC_OBJREF ; 
 scalar_t__ VPRC_WIRE_COUNT (int) ; 
 int /*<<< orphan*/  atomic_fcmpset_int (int*,int*,int) ; 
 int vm_page_busied (TYPE_1__*) ; 
 int vm_page_drop (TYPE_1__*,int) ; 

__attribute__((used)) static bool
vm_page_try_blocked_op(vm_page_t m, void (*op)(vm_page_t))
{
	u_int old;

	KASSERT(m->object != NULL && (m->oflags & VPO_UNMANAGED) == 0,
	    ("vm_page_try_blocked_op: page %p has no object", m));
	KASSERT(vm_page_busied(m),
	    ("vm_page_try_blocked_op: page %p is not busy", m));
	VM_OBJECT_ASSERT_LOCKED(m->object);

	old = m->ref_count;
	do {
		KASSERT(old != 0,
		    ("vm_page_try_blocked_op: page %p has no references", m));
		if (VPRC_WIRE_COUNT(old) != 0)
			return (false);
	} while (!atomic_fcmpset_int(&m->ref_count, &old, old | VPRC_BLOCKED));

	(op)(m);

	/*
	 * If the object is read-locked, new wirings may be created via an
	 * object lookup.
	 */
	old = vm_page_drop(m, VPRC_BLOCKED);
	KASSERT(!VM_OBJECT_WOWNED(m->object) ||
	    old == (VPRC_BLOCKED | VPRC_OBJREF),
	    ("vm_page_try_blocked_op: unexpected refcount value %u for %p",
	    old, m));
	return (true);
}