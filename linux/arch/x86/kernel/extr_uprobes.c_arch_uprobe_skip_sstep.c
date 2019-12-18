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
struct pt_regs {int flags; } ;
struct arch_uprobe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGTRAP ; 
 int X86_EFLAGS_TF ; 
 int __skip_sstep (struct arch_uprobe*,struct pt_regs*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  send_sig (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool arch_uprobe_skip_sstep(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	bool ret = __skip_sstep(auprobe, regs);
	if (ret && (regs->flags & X86_EFLAGS_TF))
		send_sig(SIGTRAP, current, 0);
	return ret;
}