#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  db_expr_t ;

/* Variables and functions */
 int db_cmd_loop_done ; 
 int /*<<< orphan*/  db_printf (char*) ; 
 scalar_t__ kdb_dbbe_select (char*) ; 

__attribute__((used)) static void
db_gdb(db_expr_t dummy1, bool dummy2, db_expr_t dummy3, char *dummy4)
{

	if (kdb_dbbe_select("gdb") != 0) {
		db_printf("The remote GDB backend could not be selected.\n");
		return;
	}
	/*
	 * Mark that we are done in the debugger.  kdb_trap()
	 * should re-enter with the new backend.
	 */
	db_cmd_loop_done = 1;
	db_printf("(ctrl-c will return control to ddb)\n");
}