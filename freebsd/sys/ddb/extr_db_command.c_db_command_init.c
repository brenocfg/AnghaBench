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
 int N (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  db_cmd_table ; 
 int /*<<< orphan*/ * db_cmds ; 
 int /*<<< orphan*/  db_command_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * db_show_active_cmds ; 
 int /*<<< orphan*/  db_show_active_table ; 
 int /*<<< orphan*/ * db_show_all_cmds ; 
 int /*<<< orphan*/  db_show_all_table ; 
 int /*<<< orphan*/ * db_show_cmds ; 
 int /*<<< orphan*/  db_show_table ; 

void
db_command_init(void)
{
#define	N(a)	(sizeof(a) / sizeof(a[0]))
	int i;

	for (i = 0; i < N(db_cmds); i++)
		db_command_register(&db_cmd_table, &db_cmds[i]);
	for (i = 0; i < N(db_show_cmds); i++)
		db_command_register(&db_show_table, &db_show_cmds[i]);
	for (i = 0; i < N(db_show_active_cmds); i++)
		db_command_register(&db_show_active_table,
		    &db_show_active_cmds[i]);
	for (i = 0; i < N(db_show_all_cmds); i++)
		db_command_register(&db_show_all_table, &db_show_all_cmds[i]);
#undef N
}