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
#define  EBUSY 129 
#define  ENXIO 128 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int doadump (int) ; 
 scalar_t__ textdump_pending ; 

__attribute__((used)) static void
db_dump(db_expr_t dummy, bool dummy2, db_expr_t dummy3, char *dummy4)
{
	int error;

	if (textdump_pending) {
		db_printf("textdump_pending set.\n"
		    "run \"textdump unset\" first or \"textdump dump\" for a textdump.\n");
		return;
	}
	error = doadump(false);
	if (error) {
		db_printf("Cannot dump: ");
		switch (error) {
		case EBUSY:
			db_printf("debugger got invoked while dumping.\n");
			break;
		case ENXIO:
			db_printf("no dump device specified.\n");
			break;
		default:
			db_printf("unknown error (error=%d).\n", error);
			break;
		}
	}
}