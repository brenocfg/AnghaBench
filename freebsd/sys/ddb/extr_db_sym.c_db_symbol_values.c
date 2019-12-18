#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  db_expr_t ;
typedef  scalar_t__ c_db_sym_t ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ DB_SYM_NULL ; 
 int /*<<< orphan*/  X_db_symbol_values (TYPE_1__*,scalar_t__,char const**,int /*<<< orphan*/ *) ; 
 TYPE_1__* db_last_symtab ; 
 char* db_qualify (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ db_symbol_is_ambiguous (scalar_t__) ; 

void
db_symbol_values(c_db_sym_t sym, const char **namep, db_expr_t *valuep)
{
	db_expr_t	value;

	if (sym == DB_SYM_NULL) {
		*namep = NULL;
		return;
	}

	X_db_symbol_values(db_last_symtab, sym, namep, &value);

	if (db_symbol_is_ambiguous(sym))
		*namep = db_qualify(sym, db_last_symtab->name);
	if (valuep)
		*valuep = value;
}