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
 int ENOENT ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int db_read_token () ; 
 int db_script_unset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_skip_to_eol () ; 
 int /*<<< orphan*/  db_tok_string ; 
 int tIDENT ; 

void
db_unscript_cmd(db_expr_t addr, bool have_addr, db_expr_t count,
    char *modif)
{
	int error, t;

	t = db_read_token();
	if (t != tIDENT) {
		db_printf("?\n");
		db_skip_to_eol();
		return;
	}

	error = db_script_unset(db_tok_string);
	if (error == ENOENT) {
		db_printf("script '%s' not found\n", db_tok_string);
		db_skip_to_eol();
		return;
	}
	db_skip_to_eol();
}