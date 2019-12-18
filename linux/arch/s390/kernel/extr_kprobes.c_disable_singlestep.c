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
struct TYPE_2__ {unsigned long addr; int /*<<< orphan*/  mask; } ;
struct pt_regs {TYPE_1__ psw; } ;
struct kprobe_ctlblk {int /*<<< orphan*/  kprobe_saved_imask; int /*<<< orphan*/  kprobe_saved_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PSW_MASK_PER ; 
 int /*<<< orphan*/  __ctl_load (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void disable_singlestep(struct kprobe_ctlblk *kcb,
			       struct pt_regs *regs,
			       unsigned long ip)
{
	/* Restore control regs and psw mask, set new psw address */
	__ctl_load(kcb->kprobe_saved_ctl, 9, 11);
	regs->psw.mask &= ~PSW_MASK_PER;
	regs->psw.mask |= kcb->kprobe_saved_imask;
	regs->psw.addr = ip;
}