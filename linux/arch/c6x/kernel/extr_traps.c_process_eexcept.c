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

/* Variables and functions */
 int /*<<< orphan*/  EXCEPT_TYPE_EXC ; 
 int /*<<< orphan*/  ack_exception (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_trap (int /*<<< orphan*/ *,struct pt_regs*) ; 
 int /*<<< orphan*/ * eexcept_table ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int soc_get_exception () ; 

__attribute__((used)) static void process_eexcept(struct pt_regs *regs)
{
	int evt;

	pr_err("EEXCEPT: PC[0x%lx]\n", regs->pc);

	while ((evt = soc_get_exception()) >= 0)
		do_trap(&eexcept_table[evt], regs);

	ack_exception(EXCEPT_TYPE_EXC);
}