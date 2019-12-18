#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* db_breakpoint_t ;
struct TYPE_2__ {int /*<<< orphan*/  address; int /*<<< orphan*/  init_count; scalar_t__ map; struct TYPE_2__* link; } ;

/* Variables and functions */
 int /*<<< orphan*/  DB_STGY_PROC ; 
 scalar_t__ db_breakpoint_list ; 
 scalar_t__ db_map_current (scalar_t__) ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_printsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
db_list_breakpoints(void)
{
	register db_breakpoint_t	bkpt;

	if (db_breakpoint_list == 0) {
	    db_printf("No breakpoints set\n");
	    return;
	}

	db_printf(" Map      Count    Address\n");
	for (bkpt = db_breakpoint_list;
	     bkpt != 0;
	     bkpt = bkpt->link) {
	    db_printf("%s%8p %5d    ",
		      db_map_current(bkpt->map) ? "*" : " ",
		      (void *)bkpt->map, bkpt->init_count);
	    db_printsym(bkpt->address, DB_STGY_PROC);
	    db_printf("\n");
	}
}