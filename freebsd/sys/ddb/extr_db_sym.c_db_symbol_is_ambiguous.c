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
typedef  int /*<<< orphan*/  c_db_sym_t ;

/* Variables and functions */
 scalar_t__ X_db_lookup (int /*<<< orphan*/ *,char const*) ; 
 int db_nsymtab ; 
 int /*<<< orphan*/  db_qualify_ambiguous_names ; 
 int /*<<< orphan*/  db_symbol_values (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * db_symtabs ; 

__attribute__((used)) static bool
db_symbol_is_ambiguous(c_db_sym_t sym)
{
	const char	*sym_name;
	int		i;
	bool		found_once = false;

	if (!db_qualify_ambiguous_names)
		return (false);

	db_symbol_values(sym, &sym_name, 0);
	for (i = 0; i < db_nsymtab; i++) {
		if (X_db_lookup(&db_symtabs[i], sym_name)) {
			if (found_once)
				return (true);
			found_once = true;
		}
	}
	return (false);
}