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
struct pt_regs {int /*<<< orphan*/  gp; int /*<<< orphan*/  r28; int /*<<< orphan*/  r27; int /*<<< orphan*/  r25; int /*<<< orphan*/  r24; int /*<<< orphan*/  r23; int /*<<< orphan*/  r22; int /*<<< orphan*/  r21; int /*<<< orphan*/  r20; int /*<<< orphan*/  r19; int /*<<< orphan*/  r18; int /*<<< orphan*/  r17; int /*<<< orphan*/  r16; int /*<<< orphan*/  r8; int /*<<< orphan*/  r7; int /*<<< orphan*/  r6; int /*<<< orphan*/  r5; int /*<<< orphan*/  r4; int /*<<< orphan*/  r3; int /*<<< orphan*/  r2; int /*<<< orphan*/  r1; int /*<<< orphan*/  r0; scalar_t__ r26; scalar_t__ pc; int /*<<< orphan*/  ps; } ;

/* Variables and functions */
 int /*<<< orphan*/  __halt () ; 
 int /*<<< orphan*/  print_tainted () ; 
 int /*<<< orphan*/  printk (char*,void*,...) ; 

void
dik_show_regs(struct pt_regs *regs, unsigned long *r9_15)
{
	printk("pc = [<%016lx>]  ra = [<%016lx>]  ps = %04lx    %s\n",
	       regs->pc, regs->r26, regs->ps, print_tainted());
	printk("pc is at %pSR\n", (void *)regs->pc);
	printk("ra is at %pSR\n", (void *)regs->r26);
	printk("v0 = %016lx  t0 = %016lx  t1 = %016lx\n",
	       regs->r0, regs->r1, regs->r2);
	printk("t2 = %016lx  t3 = %016lx  t4 = %016lx\n",
 	       regs->r3, regs->r4, regs->r5);
	printk("t5 = %016lx  t6 = %016lx  t7 = %016lx\n",
	       regs->r6, regs->r7, regs->r8);

	if (r9_15) {
		printk("s0 = %016lx  s1 = %016lx  s2 = %016lx\n",
		       r9_15[9], r9_15[10], r9_15[11]);
		printk("s3 = %016lx  s4 = %016lx  s5 = %016lx\n",
		       r9_15[12], r9_15[13], r9_15[14]);
		printk("s6 = %016lx\n", r9_15[15]);
	}

	printk("a0 = %016lx  a1 = %016lx  a2 = %016lx\n",
	       regs->r16, regs->r17, regs->r18);
	printk("a3 = %016lx  a4 = %016lx  a5 = %016lx\n",
 	       regs->r19, regs->r20, regs->r21);
 	printk("t8 = %016lx  t9 = %016lx  t10= %016lx\n",
	       regs->r22, regs->r23, regs->r24);
	printk("t11= %016lx  pv = %016lx  at = %016lx\n",
	       regs->r25, regs->r27, regs->r28);
	printk("gp = %016lx  sp = %p\n", regs->gp, regs+1);
#if 0
__halt();
#endif
}