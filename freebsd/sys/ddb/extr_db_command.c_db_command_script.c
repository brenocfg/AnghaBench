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
 int /*<<< orphan*/  db_cmd_table ; 
 int /*<<< orphan*/  db_command (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_dot ; 
 int /*<<< orphan*/  db_inject_line (char const*) ; 
 int /*<<< orphan*/  db_last_command ; 
 int /*<<< orphan*/  db_next ; 
 int /*<<< orphan*/  db_prev ; 

void
db_command_script(const char *command)
{
	db_prev = db_next = db_dot;
	db_inject_line(command);
	db_command(&db_last_command, &db_cmd_table, /* dopager */ 0);
}