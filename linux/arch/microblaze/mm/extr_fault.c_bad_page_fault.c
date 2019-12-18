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
struct pt_regs {int /*<<< orphan*/  pc; } ;
struct exception_table_entry {int /*<<< orphan*/  fixup; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*,struct pt_regs*,int) ; 
 struct exception_table_entry* search_exception_tables (int /*<<< orphan*/ ) ; 

void bad_page_fault(struct pt_regs *regs, unsigned long address, int sig)
{
	const struct exception_table_entry *fixup;
/* MS: no context */
	/* Are we prepared to handle this fault?  */
	fixup = search_exception_tables(regs->pc);
	if (fixup) {
		regs->pc = fixup->fixup;
		return;
	}

	/* kernel has accessed a bad area */
	die("kernel access of bad area", regs, sig);
}