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
typedef  int /*<<< orphan*/  c_db_sym_t ;

/* Variables and functions */
 int X_db_line_at_pc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  db_last_symtab ; 

__attribute__((used)) static bool
db_line_at_pc(c_db_sym_t sym, char **filename, int *linenum, db_expr_t pc)
{
	return (X_db_line_at_pc(db_last_symtab, sym, filename, linenum, pc));
}