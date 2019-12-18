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
struct trapframe {int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_rflags; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_fs; int /*<<< orphan*/  tf_gs; } ;
struct thread {int /*<<< orphan*/  td_pcb; struct trapframe* td_frame; } ;
struct reg32 {int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_esp; int /*<<< orphan*/  r_eflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_eip; int /*<<< orphan*/  r_eax; int /*<<< orphan*/  r_ecx; int /*<<< orphan*/  r_edx; int /*<<< orphan*/  r_ebx; int /*<<< orphan*/  r_ebp; int /*<<< orphan*/  r_esi; int /*<<< orphan*/  r_edi; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_fs; int /*<<< orphan*/  r_gs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SECURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFL_SECURE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int /*<<< orphan*/  TF_HASSEGS ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
set_regs32(struct thread *td, struct reg32 *regs)
{
	struct trapframe *tp;

	tp = td->td_frame;
	if (!EFL_SECURE(regs->r_eflags, tp->tf_rflags) || !CS_SECURE(regs->r_cs))
		return (EINVAL);
	tp->tf_gs = regs->r_gs;
	tp->tf_fs = regs->r_fs;
	tp->tf_es = regs->r_es;
	tp->tf_ds = regs->r_ds;
	set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
	tp->tf_flags = TF_HASSEGS;
	tp->tf_rdi = regs->r_edi;
	tp->tf_rsi = regs->r_esi;
	tp->tf_rbp = regs->r_ebp;
	tp->tf_rbx = regs->r_ebx;
	tp->tf_rdx = regs->r_edx;
	tp->tf_rcx = regs->r_ecx;
	tp->tf_rax = regs->r_eax;
	tp->tf_rip = regs->r_eip;
	tp->tf_cs = regs->r_cs;
	tp->tf_rflags = regs->r_eflags;
	tp->tf_rsp = regs->r_esp;
	tp->tf_ss = regs->r_ss;
	return (0);
}