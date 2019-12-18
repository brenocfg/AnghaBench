#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ c_db_sym_t ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ X_db_lookup (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  db_error (char*) ; 
 TYPE_1__* db_last_symtab ; 
 int db_nsymtab ; 
 TYPE_1__* db_symtabs ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static c_db_sym_t
db_lookup(const char *symstr)
{
	c_db_sym_t sp;
	int i;
	int symtab_start = 0;
	int symtab_end = db_nsymtab;
	const char *cp;

	/*
	 * Look for, remove, and remember any symbol table specifier.
	 */
	for (cp = symstr; *cp; cp++) {
		if (*cp == ':') {
			for (i = 0; i < db_nsymtab; i++) {
				int n = strlen(db_symtabs[i].name);

				if (
				    n == (cp - symstr) &&
				    strncmp(symstr, db_symtabs[i].name, n) == 0
				) {
					symtab_start = i;
					symtab_end = i + 1;
					break;
				}
			}
			if (i == db_nsymtab) {
				db_error("invalid symbol table name");
			}
			symstr = cp+1;
		}
	}

	/*
	 * Look in the specified set of symbol tables.
	 * Return on first match.
	 */
	for (i = symtab_start; i < symtab_end; i++) {
		sp = X_db_lookup(&db_symtabs[i], symstr);
		if (sp) {
			db_last_symtab = &db_symtabs[i];
			return sp;
		}
	}
	return 0;
}