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
 int /*<<< orphan*/  db_error (char*) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_script_exec (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  db_tok_string ; 
 int tEOL ; 
 int tIDENT ; 

void
db_run_cmd(db_expr_t addr, bool have_addr, db_expr_t count, char *modif)
{
	int t;

	/*
	 * Right now, we accept exactly one argument.  In the future, we
	 * might want to accept flags and arguments to the script itself.
	 */
	t = db_read_token();
	if (t != tIDENT)
		db_error("?\n");

	if (db_read_token() != tEOL)
		db_error("?\n");

	db_script_exec(db_tok_string, 1);
}