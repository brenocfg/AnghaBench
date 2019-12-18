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
typedef  int /*<<< orphan*/  c_db_sym_t ;

/* Variables and functions */

bool
X_db_sym_numargs(db_symtab_t *symtab, c_db_sym_t sym, int *nargp,
    char **argp)
{
	return (false);
}