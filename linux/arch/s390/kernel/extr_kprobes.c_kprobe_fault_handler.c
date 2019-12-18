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

/* Variables and functions */
 int PSW_MASK_EXT ; 
 int PSW_MASK_IO ; 
 int PSW_MASK_PER ; 
 int kprobe_trap_handler (struct pt_regs*,int) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_restore (int) ; 

int kprobe_fault_handler(struct pt_regs *regs, int trapnr)
{
	int ret;

	if (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_disable();
	ret = kprobe_trap_handler(regs, trapnr);
	if (regs->psw.mask & (PSW_MASK_IO | PSW_MASK_EXT))
		local_irq_restore(regs->psw.mask & ~PSW_MASK_PER);
	return ret;
}