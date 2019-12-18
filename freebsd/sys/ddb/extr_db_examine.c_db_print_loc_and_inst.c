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
typedef  int /*<<< orphan*/  db_addr_t ;

/* Variables and functions */
 scalar_t__ C_DB_SYM_NULL ; 
 int /*<<< orphan*/  DB_STGY_PROC ; 
 int /*<<< orphan*/  db_disasm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  db_printf (char*) ; 
 int /*<<< orphan*/  db_printsym (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ db_search_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
db_print_loc_and_inst(db_addr_t loc)
{
	db_expr_t off;

	db_printsym(loc, DB_STGY_PROC);
	if (db_search_symbol(loc, DB_STGY_PROC, &off) != C_DB_SYM_NULL) {
		db_printf(":\t");
		(void)db_disasm(loc, false);
	}
}