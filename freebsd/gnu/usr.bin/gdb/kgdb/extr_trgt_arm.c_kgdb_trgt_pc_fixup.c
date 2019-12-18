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
struct minimal_symbol {int dummy; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_SYMBOL_NAME (struct minimal_symbol*) ; 
 struct minimal_symbol* lookup_minimal_symbol_by_pc (scalar_t__) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  target_read_memory (scalar_t__,char*,int) ; 

int
kgdb_trgt_pc_fixup(CORE_ADDR *pc)
{
#ifndef CROSS_DEBUGGER
	struct minimal_symbol *msymbol;
	int valpc;

	/*
	 * exception_exit and swi_exit are special. These functions
	 * are artificially injected into the stack to be executed
	 * as the last entry in calling chain when all functions exit.
	 * Treat them differently.
	 */
	msymbol = lookup_minimal_symbol_by_pc(*pc);
	if (msymbol != NULL) {
		if (strcmp(DEPRECATED_SYMBOL_NAME(msymbol), "exception_exit") == 0)
			return (0);
		if (strcmp(DEPRECATED_SYMBOL_NAME(msymbol), "swi_exit") == 0)
			return (0);
	}

	/*
	 * kdb_enter contains an invalid instruction which is supposed
	 * to generate a trap. BFD does not understand it and treats
	 * this part of function as a separate function. Move PC
	 * two instruction earlier to be inside kdb_enter section.
	 */
	target_read_memory(*pc - 4, (char*)&valpc, 4);
	if (valpc == 0xe7ffffff) {
		*pc = *pc - 8;
		return (0);
	}

	/*
	 * When the panic/vpanic is the last (noreturn) function,
	 * the bottom of the calling function looks as below.
	 *   mov lr, pc
	 *   b panic
	 * Normally, GDB is not able to detect function boundaries,
	 * so move the PC two instruction earlier where it can deal
	 * with it.
	 * Match this pair of instructions: mov lr, pc followed with
	 * non-linked branch.
	 */
	if ((valpc & 0xff000000) == 0xea000000) {
		target_read_memory(*pc - 8, (char*)&valpc, 4);
		if (valpc == 0xe1a0e00f) {
			*pc -= 8;
			return (0);
		}
	}
#endif
	return (-1);
}