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
struct pt_regs {int /*<<< orphan*/  sp; } ;
struct arch_uprobe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ERESTART ; 
 int /*<<< orphan*/  branch_is_call (struct arch_uprobe*) ; 
 scalar_t__ sizeof_long (struct pt_regs*) ; 

__attribute__((used)) static int branch_post_xol_op(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	BUG_ON(!branch_is_call(auprobe));
	/*
	 * We can only get here if branch_emulate_op() failed to push the ret
	 * address _and_ another thread expanded our stack before the (mangled)
	 * "call" insn was executed out-of-line. Just restore ->sp and restart.
	 * We could also restore ->ip and try to call branch_emulate_op() again.
	 */
	regs->sp += sizeof_long(regs);
	return -ERESTART;
}