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
typedef  int /*<<< orphan*/  db_symtab_t ;
typedef  int /*<<< orphan*/  db_expr_t ;
typedef  int /*<<< orphan*/  c_db_sym_t ;

/* Variables and functions */

bool
X_db_line_at_pc(db_symtab_t *symtab, c_db_sym_t sym, char **file, int *line,
    db_expr_t off)
{
	return (false);
}