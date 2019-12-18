#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  ref_count; int /*<<< orphan*/ * object; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PG_FICTITIOUS ; 
 int /*<<< orphan*/  VM_OBJECT_ASSERT_LOCKED (int /*<<< orphan*/ *) ; 
 scalar_t__ VPRC_WIRE_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ VPRC_WIRE_COUNT_MAX ; 
 int /*<<< orphan*/  atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vm_page_busied (TYPE_1__*) ; 
 int /*<<< orphan*/  vm_wire_add (int) ; 

void
vm_page_wire(vm_page_t m)
{
	u_int old;

	KASSERT(m->object != NULL,
	    ("vm_page_wire: page %p does not belong to an object", m));
	if (!vm_page_busied(m))
		VM_OBJECT_ASSERT_LOCKED(m->object);
	KASSERT((m->flags & PG_FICTITIOUS) == 0 ||
	    VPRC_WIRE_COUNT(m->ref_count) >= 1,
	    ("vm_page_wire: fictitious page %p has zero wirings", m));

	old = atomic_fetchadd_int(&m->ref_count, 1);
	KASSERT(VPRC_WIRE_COUNT(old) != VPRC_WIRE_COUNT_MAX,
	    ("vm_page_wire: counter overflow for page %p", m));
	if (VPRC_WIRE_COUNT(old) == 0)
		vm_wire_add(1);
}