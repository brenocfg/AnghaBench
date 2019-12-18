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
struct pt_regs {int /*<<< orphan*/  cp0_epc; } ;
struct exception_table_entry {int /*<<< orphan*/  nextinsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  exception_epc (struct pt_regs*) ; 
 struct exception_table_entry* search_exception_tables (int /*<<< orphan*/ ) ; 

int fixup_exception(struct pt_regs *regs)
{
	const struct exception_table_entry *fixup;

	fixup = search_exception_tables(exception_epc(regs));
	if (fixup) {
		regs->cp0_epc = fixup->nextinsn;

		return 1;
	}

	return 0;
}