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
typedef  scalar_t__ vm_size_t ;
typedef  int /*<<< orphan*/ * vm_map_t ;
typedef  TYPE_1__* db_watchpoint_t ;
typedef  scalar_t__ db_addr_t ;
struct TYPE_4__ {scalar_t__ loaddr; scalar_t__ hiaddr; struct TYPE_4__* link; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 scalar_t__ db_map_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_printf (char*) ; 
 TYPE_1__* db_watchpoint_alloc () ; 
 TYPE_1__* db_watchpoint_list ; 
 int db_watchpoints_inserted ; 

__attribute__((used)) static void
db_set_watchpoint(vm_map_t map, db_addr_t addr, vm_size_t size)
{
	db_watchpoint_t	watch;

	if (map == NULL) {
	    db_printf("No map.\n");
	    return;
	}

	/*
	 *	Should we do anything fancy with overlapping regions?
	 */

	for (watch = db_watchpoint_list;
	     watch != 0;
	     watch = watch->link)
	    if (db_map_equal(watch->map, map) &&
		(watch->loaddr == addr) &&
		(watch->hiaddr == addr+size)) {
		db_printf("Already set.\n");
		return;
	    }

	watch = db_watchpoint_alloc();
	if (watch == 0) {
	    db_printf("Too many watchpoints.\n");
	    return;
	}

	watch->map = map;
	watch->loaddr = addr;
	watch->hiaddr = addr+size;

	watch->link = db_watchpoint_list;
	db_watchpoint_list = watch;

	db_watchpoints_inserted = false;
}