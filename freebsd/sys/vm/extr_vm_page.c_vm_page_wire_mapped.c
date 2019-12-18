#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int u_int ;
struct TYPE_3__ {int ref_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int VPRC_BLOCKED ; 
 scalar_t__ VPRC_WIRE_COUNT (int) ; 
 int /*<<< orphan*/  atomic_fcmpset_int (int*,int*,int) ; 
 int /*<<< orphan*/  vm_wire_add (int) ; 

bool
vm_page_wire_mapped(vm_page_t m)
{
	u_int old;

	old = m->ref_count;
	do {
		KASSERT(old > 0,
		    ("vm_page_wire_mapped: wiring unreferenced page %p", m));
		if ((old & VPRC_BLOCKED) != 0)
			return (false);
	} while (!atomic_fcmpset_int(&m->ref_count, &old, old + 1));

	if (VPRC_WIRE_COUNT(old) == 0)
		vm_wire_add(1);
	return (true);
}