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
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  TYPE_1__* db_breakpoint_t ;
typedef  scalar_t__ db_addr_t ;
struct TYPE_4__ {scalar_t__ address; struct TYPE_4__* link; int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int /*<<< orphan*/  db_breakpoint_free (TYPE_1__*) ; 
 TYPE_1__* db_breakpoint_list ; 
 scalar_t__ db_map_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_printf (char*) ; 

__attribute__((used)) static void
db_delete_breakpoint(vm_map_t map, db_addr_t addr)
{
	register db_breakpoint_t	bkpt;
	register db_breakpoint_t	*prev;

	for (prev = &db_breakpoint_list;
	     (bkpt = *prev) != 0;
	     prev = &bkpt->link) {
	    if (db_map_equal(bkpt->map, map) &&
		(bkpt->address == addr)) {
		*prev = bkpt->link;
		break;
	    }
	}
	if (bkpt == 0) {
	    db_printf("Not set.\n");
	    return;
	}

	db_breakpoint_free(bkpt);
}