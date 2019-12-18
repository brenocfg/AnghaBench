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
struct trapframe {int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_esp; int /*<<< orphan*/  tf_eflags; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_eip; int /*<<< orphan*/  tf_eax; int /*<<< orphan*/  tf_ecx; int /*<<< orphan*/  tf_edx; int /*<<< orphan*/  tf_ebx; int /*<<< orphan*/  tf_ebp; int /*<<< orphan*/  tf_esi; int /*<<< orphan*/  tf_edi; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_fs; } ;
struct thread {struct pcb* td_pcb; struct trapframe* td_frame; } ;
struct reg {int /*<<< orphan*/  r_gs; int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_esp; int /*<<< orphan*/  r_eflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_eip; int /*<<< orphan*/  r_eax; int /*<<< orphan*/  r_ecx; int /*<<< orphan*/  r_edx; int /*<<< orphan*/  r_ebx; int /*<<< orphan*/  r_ebp; int /*<<< orphan*/  r_esi; int /*<<< orphan*/  r_edi; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_fs; } ;
struct pcb {int /*<<< orphan*/  pcb_gs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SECURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFL_SECURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 

int
set_regs(struct thread *td, struct reg *regs)
{
	struct pcb *pcb;
	struct trapframe *tp;

	tp = td->td_frame;
	if (!EFL_SECURE(regs->r_eflags, tp->tf_eflags) ||
	    !CS_SECURE(regs->r_cs))
		return (EINVAL);
	pcb = td->td_pcb;
	tp->tf_fs = regs->r_fs;
	tp->tf_es = regs->r_es;
	tp->tf_ds = regs->r_ds;
	tp->tf_edi = regs->r_edi;
	tp->tf_esi = regs->r_esi;
	tp->tf_ebp = regs->r_ebp;
	tp->tf_ebx = regs->r_ebx;
	tp->tf_edx = regs->r_edx;
	tp->tf_ecx = regs->r_ecx;
	tp->tf_eax = regs->r_eax;
	tp->tf_eip = regs->r_eip;
	tp->tf_cs = regs->r_cs;
	tp->tf_eflags = regs->r_eflags;
	tp->tf_esp = regs->r_esp;
	tp->tf_ss = regs->r_ss;
	pcb->pcb_gs = regs->r_gs;
	return (0);
}