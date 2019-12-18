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
struct pt_regs {int /*<<< orphan*/ * iasq; int /*<<< orphan*/ * iaoq; int /*<<< orphan*/  cr27; int /*<<< orphan*/  ipsw; int /*<<< orphan*/  ior; int /*<<< orphan*/  isr; int /*<<< orphan*/  iir; int /*<<< orphan*/  sar; int /*<<< orphan*/ * sr; int /*<<< orphan*/  fr; int /*<<< orphan*/  gr; } ;
struct parisc_gdb_regs {int /*<<< orphan*/  iasq_b; int /*<<< orphan*/  iaoq_b; int /*<<< orphan*/  iasq_f; int /*<<< orphan*/  iaoq_f; int /*<<< orphan*/  cr27; int /*<<< orphan*/  ipsw; int /*<<< orphan*/  ior; int /*<<< orphan*/  isr; int /*<<< orphan*/  iir; int /*<<< orphan*/  sar; int /*<<< orphan*/  sr7; int /*<<< orphan*/  sr6; int /*<<< orphan*/  sr5; int /*<<< orphan*/  sr4; int /*<<< orphan*/  sr3; int /*<<< orphan*/  sr2; int /*<<< orphan*/  sr1; int /*<<< orphan*/  sr0; int /*<<< orphan*/  fr; int /*<<< orphan*/  gpr; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void gdb_regs_to_pt_regs(unsigned long *gdb_regs, struct pt_regs *regs)
{
	struct parisc_gdb_regs *gr = (struct parisc_gdb_regs *)gdb_regs;


	memcpy(regs->gr, gr->gpr, sizeof(regs->gr));
	memcpy(regs->fr, gr->fr, sizeof(regs->fr));

	regs->sr[0] = gr->sr0;
	regs->sr[1] = gr->sr1;
	regs->sr[2] = gr->sr2;
	regs->sr[3] = gr->sr3;
	regs->sr[4] = gr->sr4;
	regs->sr[5] = gr->sr5;
	regs->sr[6] = gr->sr6;
	regs->sr[7] = gr->sr7;

	regs->sar = gr->sar;
	regs->iir = gr->iir;
	regs->isr = gr->isr;
	regs->ior = gr->ior;
	regs->ipsw = gr->ipsw;
	regs->cr27 = gr->cr27;

	regs->iaoq[0] = gr->iaoq_f;
	regs->iasq[0] = gr->iasq_f;

	regs->iaoq[1] = gr->iaoq_b;
	regs->iasq[1] = gr->iasq_b;
}