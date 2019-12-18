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
struct db_variable {int /*<<< orphan*/  name; } ;
typedef  scalar_t__ db_expr_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_error (char*) ; 
 struct db_variable* db_evars ; 
 int /*<<< orphan*/  db_expression (scalar_t__*) ; 
 int /*<<< orphan*/  db_find_variable (struct db_variable**) ; 
 int /*<<< orphan*/  db_printf (char*,int /*<<< orphan*/ ,...) ; 
 int db_read_token () ; 
 int /*<<< orphan*/  db_read_variable (struct db_variable*,scalar_t__*) ; 
 int /*<<< orphan*/  db_unread_token (int) ; 
 struct db_variable* db_vars ; 
 int /*<<< orphan*/  db_write_variable (struct db_variable*,scalar_t__) ; 
 int tDOLLAR ; 
 int tEOL ; 
 int tEQ ; 

void
db_set_cmd(db_expr_t dummy1, bool dummy2, db_expr_t dummy3, char *dummy4)
{
	struct db_variable *vp;
	db_expr_t value;
	int t;

	t = db_read_token();
	if (t == tEOL) {
		for (vp = db_vars; vp < db_evars; vp++) {
			if (!db_read_variable(vp, &value)) {
				db_printf("$%s\n", vp->name);
				continue;
			}
			db_printf("$%-8s = %ld\n",
			    vp->name, (unsigned long)value);
		}
		return;
	}
	if (t != tDOLLAR) {
		db_error("Unknown variable\n");
		return;
	}
	if (!db_find_variable(&vp)) {
		db_error("Unknown variable\n");
		return;
	}

	t = db_read_token();
	if (t != tEQ)
		db_unread_token(t);

	if (!db_expression(&value)) {
		db_error("No value\n");
		return;
	}
	if (db_read_token() != tEOL)
		db_error("?\n");

	db_write_variable(vp, value);
}