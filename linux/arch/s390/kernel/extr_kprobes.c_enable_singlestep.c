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
struct TYPE_2__ {int mask; unsigned long addr; } ;
struct pt_regs {TYPE_1__ psw; } ;
struct per_regs {unsigned long start; unsigned long end; int /*<<< orphan*/  control; } ;
struct kprobe_ctlblk {int kprobe_saved_imask; int /*<<< orphan*/  kprobe_saved_ctl; } ;

/* Variables and functions */
 int /*<<< orphan*/  PER_EVENT_IFETCH ; 
 int PSW_MASK_EXT ; 
 int PSW_MASK_IO ; 
 int PSW_MASK_PER ; 
 int /*<<< orphan*/  __ctl_load (struct per_regs,int,int) ; 
 int /*<<< orphan*/  __ctl_store (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void enable_singlestep(struct kprobe_ctlblk *kcb,
			      struct pt_regs *regs,
			      unsigned long ip)
{
	struct per_regs per_kprobe;

	/* Set up the PER control registers %cr9-%cr11 */
	per_kprobe.control = PER_EVENT_IFETCH;
	per_kprobe.start = ip;
	per_kprobe.end = ip;

	/* Save control regs and psw mask */
	__ctl_store(kcb->kprobe_saved_ctl, 9, 11);
	kcb->kprobe_saved_imask = regs->psw.mask &
		(PSW_MASK_PER | PSW_MASK_IO | PSW_MASK_EXT);

	/* Set PER control regs, turns on single step for the given address */
	__ctl_load(per_kprobe, 9, 11);
	regs->psw.mask |= PSW_MASK_PER;
	regs->psw.mask &= ~(PSW_MASK_IO | PSW_MASK_EXT);
	regs->psw.addr = ip;
}