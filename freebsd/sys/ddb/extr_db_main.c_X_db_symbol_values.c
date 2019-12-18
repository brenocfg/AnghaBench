#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ value; scalar_t__ name; } ;
typedef  TYPE_1__ linker_symval_t ;
struct TYPE_7__ {int /*<<< orphan*/ * private; } ;
typedef  TYPE_2__ db_symtab_t ;
typedef  scalar_t__ db_expr_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;
typedef  scalar_t__ c_db_sym_t ;
struct TYPE_8__ {int st_name; scalar_t__ st_value; } ;
typedef  TYPE_3__ Elf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  linker_ddb_symbol_values (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
X_db_symbol_values(db_symtab_t *symtab, c_db_sym_t sym, const char **namep,
    db_expr_t *valp)
{
	linker_symval_t lval;

	if (symtab->private == NULL) {
		linker_ddb_symbol_values((c_linker_sym_t)sym, &lval);
		if (namep != NULL)
			*namep = (const char*)lval.name;
		if (valp != NULL)
			*valp = (db_expr_t)lval.value;
	} else {
		if (namep != NULL)
			*namep = (const char *)symtab->private +
			    ((const Elf_Sym *)sym)->st_name;
		if (valp != NULL)
			*valp = (db_expr_t)((const Elf_Sym *)sym)->st_value;
	}
}