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
struct alt_instr {unsigned long alt_len; } ;

/* Variables and functions */
 scalar_t__ ALT_REPL_PTR (struct alt_instr*) ; 
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ kernel_text_address (unsigned long) ; 

__attribute__((used)) static bool branch_insn_requires_update(struct alt_instr *alt, unsigned long pc)
{
	unsigned long replptr;

	if (kernel_text_address(pc))
		return true;

	replptr = (unsigned long)ALT_REPL_PTR(alt);
	if (pc >= replptr && pc <= (replptr + alt->alt_len))
		return false;

	/*
	 * Branching into *another* alternate sequence is doomed, and
	 * we're not even trying to fix it up.
	 */
	BUG();
}