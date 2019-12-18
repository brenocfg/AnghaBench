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
typedef  int /*<<< orphan*/  linker_symval_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;

/* Variables and functions */
 int linker_debug_symbol_values (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
linker_ddb_symbol_values(c_linker_sym_t sym, linker_symval_t *symval)
{

	return (linker_debug_symbol_values(sym, symval));
}