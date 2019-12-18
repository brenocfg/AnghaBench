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
typedef  unsigned long db_expr_t ;
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PC_REGS () ; 
 struct db_variable* db_eregs ; 
 int /*<<< orphan*/  db_find_xtrn_sym_and_offset (int /*<<< orphan*/ ,char const**,unsigned long*) ; 
 scalar_t__ db_maxoff ; 
 int /*<<< orphan*/  db_print_loc_and_inst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_printf (char*,...) ; 
 int /*<<< orphan*/  db_read_variable (struct db_variable*,unsigned long*) ; 
 struct db_variable* db_regs ; 

void
db_show_regs(db_expr_t _1, bool _2, db_expr_t _3, char *_4)
{
	struct db_variable *regp;
	db_expr_t value, offset;
	const char *name;

	for (regp = db_regs; regp < db_eregs; regp++) {
		if (!db_read_variable(regp, &value))
			continue;
		db_printf("%-12s%#*lr", regp->name,
		    (int)(sizeof(unsigned long) * 2 + 2), (unsigned long)value);
		db_find_xtrn_sym_and_offset((db_addr_t)value, &name, &offset);
		if (name != NULL && offset <= (unsigned long)db_maxoff &&
		    offset != value) {
			db_printf("\t%s", name);
			if (offset != 0)
				db_printf("+%+#lr", (long)offset);
		}
		db_printf("\n");
	}
	db_print_loc_and_inst(PC_REGS());
}