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
typedef  int /*<<< orphan*/  caddr_t ;
typedef  int /*<<< orphan*/  c_linker_sym_t ;

/* Variables and functions */
 int linker_debug_search_symbol (int /*<<< orphan*/ ,int /*<<< orphan*/ *,long*) ; 

int
linker_ddb_search_symbol(caddr_t value, c_linker_sym_t *sym, long *diffp)
{

	return (linker_debug_search_symbol(value, sym, diffp));
}