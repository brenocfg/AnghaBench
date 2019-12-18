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
 int /*<<< orphan*/  db_capture_bufoff ; 
 int /*<<< orphan*/  db_capture_bufsize ; 
 scalar_t__ db_capture_inprogress ; 
 int /*<<< orphan*/  db_capture_reset () ; 
 int /*<<< orphan*/  db_capture_start () ; 
 int /*<<< orphan*/  db_capture_stop () ; 
 int /*<<< orphan*/  db_capture_usage () ; 
 int /*<<< orphan*/  db_error (char*) ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_tok_string ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int tEOL ; 
 int tIDENT ; 

void
db_capture_cmd(db_expr_t addr, bool have_addr, db_expr_t count, char *modif)
{
	int t;

	t = db_read_token();
	if (t != tIDENT) {
		db_capture_usage();
		return;
	}
	if (db_read_token() != tEOL)
		db_error("?\n");
	if (strcmp(db_tok_string, "on") == 0)
		db_capture_start();
	else if (strcmp(db_tok_string, "off") == 0)
		db_capture_stop();
	else if (strcmp(db_tok_string, "reset") == 0)
		db_capture_reset();
	else if (strcmp(db_tok_string, "status") == 0) {
		db_printf("%u/%u bytes used\n", db_capture_bufoff,
		    db_capture_bufsize);
		if (db_capture_inprogress)
			db_printf("capture is on\n");
		else
			db_printf("capture is off\n");
	} else
		db_capture_usage();
}