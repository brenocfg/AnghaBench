#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int mask; } ;
struct pt_regs {TYPE_1__ psw; } ;
struct notifier_block {int dummy; } ;
struct die_args {int /*<<< orphan*/  trapnr; struct pt_regs* regs; } ;

/* Variables and functions */
#define  DIE_BPT 130 
#define  DIE_SSTEP 129 
#define  DIE_TRAP 128 
 int NOTIFY_DONE ; 
 int NOTIFY_STOP ; 
 int PSW_MASK_EXT ; 
 int PSW_MASK_IO ; 
 int PSW_MASK_PER ; 
 int /*<<< orphan*/  kprobe_handler (struct pt_regs*) ; 
 int /*<<< orphan*/  kprobe_running () ; 
 int /*<<< orphan*/  kprobe_trap_handler (struct pt_regs*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (int) ; 
 int /*<<< orphan*/  post_kprobe_handler (struct pt_regs*) ; 
 int /*<<< orphan*/  preemptible () ; 

int kprobe_exceptions_notify(struct notifier_block *self,
			     unsigned long val, void *data)
{
	struct die_args *args = (struct die_args *) data;
	struct pt_regs *regs = args->regs;
	int ret = NOTIFY_DONE;

	if (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_disable();

	switch (val) {
	case DIE_BPT:
		if (kprobe_handler(regs))
			ret = NOTIFY_STOP;
		break;
	case DIE_SSTEP:
		if (post_kprobe_handler(regs))
			ret = NOTIFY_STOP;
		break;
	case DIE_TRAP:
		if (!preemptible() && kprobe_running() &&
		    kprobe_trap_handler(regs, args->trapnr))
			ret = NOTIFY_STOP;
		break;
	default:
		break;
	}

	if (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_restore(regs->psw.mask & ~PSW_MASK_PER);

	return ret;
}