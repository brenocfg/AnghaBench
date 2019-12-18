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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  c_db_sym_t ;

/* Variables and functions */
 int /*<<< orphan*/  db_symbol_values (int /*<<< orphan*/ ,char const**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char const*) ; 

__attribute__((used)) static char *
db_qualify(c_db_sym_t sym, char *symtabname)
{
	const char	*symname;
	static char     tmp[256];

	db_symbol_values(sym, &symname, 0);
	snprintf(tmp, sizeof(tmp), "%s:%s", symtabname, symname);
	return tmp;
}