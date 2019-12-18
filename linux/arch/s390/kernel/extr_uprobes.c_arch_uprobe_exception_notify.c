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
struct pt_regs {int int_code; } ;
struct notifier_block {int dummy; } ;
struct die_args {struct pt_regs* regs; } ;

/* Variables and functions */
#define  DIE_BPT 129 
#define  DIE_SSTEP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int /*<<< orphan*/  uprobe_post_sstep_notifier (struct pt_regs*) ; 
 int /*<<< orphan*/  uprobe_pre_sstep_notifier (struct pt_regs*) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

int arch_uprobe_exception_notify(struct notifier_block *self, unsigned long val,
				 void *data)
{
	struct die_args *args = data;
	struct pt_regs *regs = args->regs;

	if (!user_mode(regs))
		return NOTIFY_DONE;
	if (regs->int_code & 0x200) /* Trap during transaction */
		return NOTIFY_DONE;
	switch (val) {
	case DIE_BPT:
		if (uprobe_pre_sstep_notifier(regs))
			return NOTIFY_STOP;
		break;
	case DIE_SSTEP:
		if (uprobe_post_sstep_notifier(regs))
			return NOTIFY_STOP;
	default:
		break;
	}
	return NOTIFY_DONE;
}