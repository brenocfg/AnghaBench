#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* end; int /*<<< orphan*/ * private; scalar_t__ start; } ;
typedef  TYPE_1__ db_symtab_t ;
typedef  int /*<<< orphan*/ * c_linker_sym_t ;
typedef  int /*<<< orphan*/ * c_db_sym_t ;
struct TYPE_5__ {scalar_t__ st_name; } ;
typedef  TYPE_2__ Elf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  linker_ddb_lookup (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char const*) ; 

c_db_sym_t
X_db_lookup(db_symtab_t *symtab, const char *symbol)
{
	c_linker_sym_t lsym;
	Elf_Sym *sym;

	if (symtab->private == NULL) {
		return ((c_db_sym_t)((!linker_ddb_lookup(symbol, &lsym))
			? lsym : NULL));
	} else {
		sym = (Elf_Sym *)symtab->start;
		while ((char *)sym < symtab->end) {
			if (sym->st_name != 0 &&
			    !strcmp(symtab->private + sym->st_name, symbol))
				return ((c_db_sym_t)sym);
			sym++;
		}
	}
	return (NULL);
}