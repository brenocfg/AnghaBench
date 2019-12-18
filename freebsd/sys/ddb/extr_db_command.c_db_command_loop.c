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

/* Variables and functions */
 scalar_t__ db_cmd_loop_done ; 
 int /*<<< orphan*/  db_cmd_table ; 
 int /*<<< orphan*/  db_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 void* db_dot ; 
 int /*<<< orphan*/  db_last_command ; 
 void* db_next ; 
 void* db_prev ; 
 scalar_t__ db_print_position () ; 
 int /*<<< orphan*/  db_printf (char*) ; 
 int /*<<< orphan*/  db_read_line () ; 

void
db_command_loop(void)
{
	/*
	 * Initialize 'prev' and 'next' to dot.
	 */
	db_prev = db_dot;
	db_next = db_dot;

	db_cmd_loop_done = 0;
	while (!db_cmd_loop_done) {
	    if (db_print_position() != 0)
		db_printf("\n");

	    db_printf("db> ");
	    (void) db_read_line();

	    db_command(&db_last_command, &db_cmd_table, /* dopager */ 1);
	}
}