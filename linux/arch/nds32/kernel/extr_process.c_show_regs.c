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
struct pt_regs {char** uregs; int /*<<< orphan*/  gp; int /*<<< orphan*/  fp; int /*<<< orphan*/  sp; scalar_t__ lp; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERNEL_DS ; 
 int /*<<< orphan*/  get_fs () ; 
 scalar_t__ instruction_pointer (struct pt_regs*) ; 
 scalar_t__ interrupts_enabled (struct pt_regs*) ; 
 int /*<<< orphan*/  pr_info (char*,char*,char*,...) ; 
 int /*<<< orphan*/  print_tainted () ; 
 int /*<<< orphan*/  printk (char*,void*) ; 
 scalar_t__ segment_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void show_regs(struct pt_regs *regs)
{
	printk("PC is at %pS\n", (void *)instruction_pointer(regs));
	printk("LP is at %pS\n", (void *)regs->lp);
	pr_info("pc : [<%08lx>]    lp : [<%08lx>]    %s\n"
		"sp : %08lx  fp : %08lx  gp : %08lx\n",
		instruction_pointer(regs),
		regs->lp, print_tainted(), regs->sp, regs->fp, regs->gp);
	pr_info("r25: %08lx  r24: %08lx\n", regs->uregs[25], regs->uregs[24]);

	pr_info("r23: %08lx  r22: %08lx  r21: %08lx  r20: %08lx\n",
		regs->uregs[23], regs->uregs[22],
		regs->uregs[21], regs->uregs[20]);
	pr_info("r19: %08lx  r18: %08lx  r17: %08lx  r16: %08lx\n",
		regs->uregs[19], regs->uregs[18],
		regs->uregs[17], regs->uregs[16]);
	pr_info("r15: %08lx  r14: %08lx  r13: %08lx  r12: %08lx\n",
		regs->uregs[15], regs->uregs[14],
		regs->uregs[13], regs->uregs[12]);
	pr_info("r11: %08lx  r10: %08lx  r9 : %08lx  r8 : %08lx\n",
		regs->uregs[11], regs->uregs[10],
		regs->uregs[9], regs->uregs[8]);
	pr_info("r7 : %08lx  r6 : %08lx  r5 : %08lx  r4 : %08lx\n",
		regs->uregs[7], regs->uregs[6], regs->uregs[5], regs->uregs[4]);
	pr_info("r3 : %08lx  r2 : %08lx  r1 : %08lx  r0 : %08lx\n",
		regs->uregs[3], regs->uregs[2], regs->uregs[1], regs->uregs[0]);
	pr_info("  IRQs o%s  Segment %s\n",
		interrupts_enabled(regs) ? "n" : "ff",
		segment_eq(get_fs(), KERNEL_DS)? "kernel" : "user");
}