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
 int X_db_sym_numargs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,char**) ; 
 int /*<<< orphan*/  db_last_symtab ; 

bool
db_sym_numargs(c_db_sym_t sym, int *nargp, char **argnames)
{
	return (X_db_sym_numargs(db_last_symtab, sym, nargp, argnames));
}