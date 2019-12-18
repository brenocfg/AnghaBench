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
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PG_FICTITIOUS ; 
 int VPRC_WIRE_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_drop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  vm_wire_sub (int) ; 

bool
vm_page_unwire_noq(vm_page_t m)
{
	u_int old;

	old = vm_page_drop(m, 1);
	KASSERT(VPRC_WIRE_COUNT(old) != 0,
	    ("vm_page_unref: counter underflow for page %p", m));
	KASSERT((m->flags & PG_FICTITIOUS) == 0 || VPRC_WIRE_COUNT(old) > 1,
	    ("vm_page_unref: missing ref on fictitious page %p", m));

	if (VPRC_WIRE_COUNT(old) > 1)
		return (false);
	vm_wire_sub(1);
	return (true);
}