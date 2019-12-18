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
struct trapframe {int tf_rflags; int /*<<< orphan*/  tf_flags; int /*<<< orphan*/  tf_gs; int /*<<< orphan*/  tf_fs; int /*<<< orphan*/  tf_es; int /*<<< orphan*/  tf_ds; int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_r11; int /*<<< orphan*/  tf_r12; int /*<<< orphan*/  tf_r13; int /*<<< orphan*/  tf_r14; int /*<<< orphan*/  tf_r15; } ;
struct thread {int /*<<< orphan*/  td_pcb; struct trapframe* td_frame; } ;
struct reg {int r_rflags; int /*<<< orphan*/  r_gs; int /*<<< orphan*/  r_fs; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_rsp; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_rip; int /*<<< orphan*/  r_rax; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rbp; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdi; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r10; int /*<<< orphan*/  r_r11; int /*<<< orphan*/  r_r12; int /*<<< orphan*/  r_r13; int /*<<< orphan*/  r_r14; int /*<<< orphan*/  r_r15; } ;
typedef  int register_t ;

/* Variables and functions */
 int /*<<< orphan*/  CS_SECURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EFL_SECURE (int,int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  PCB_FULL_IRET ; 
 int /*<<< orphan*/  TF_HASSEGS ; 
 int /*<<< orphan*/  set_pcb_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
set_regs(struct thread *td, struct reg *regs)
{
	struct trapframe *tp;
	register_t rflags;

	tp = td->td_frame;
	rflags = regs->r_rflags & 0xffffffff;
	if (!EFL_SECURE(rflags, tp->tf_rflags) || !CS_SECURE(regs->r_cs))
		return (EINVAL);
	tp->tf_r15 = regs->r_r15;
	tp->tf_r14 = regs->r_r14;
	tp->tf_r13 = regs->r_r13;
	tp->tf_r12 = regs->r_r12;
	tp->tf_r11 = regs->r_r11;
	tp->tf_r10 = regs->r_r10;
	tp->tf_r9  = regs->r_r9;
	tp->tf_r8  = regs->r_r8;
	tp->tf_rdi = regs->r_rdi;
	tp->tf_rsi = regs->r_rsi;
	tp->tf_rbp = regs->r_rbp;
	tp->tf_rbx = regs->r_rbx;
	tp->tf_rdx = regs->r_rdx;
	tp->tf_rcx = regs->r_rcx;
	tp->tf_rax = regs->r_rax;
	tp->tf_rip = regs->r_rip;
	tp->tf_cs = regs->r_cs;
	tp->tf_rflags = rflags;
	tp->tf_rsp = regs->r_rsp;
	tp->tf_ss = regs->r_ss;
	if (0) {	/* XXXKIB */
		tp->tf_ds = regs->r_ds;
		tp->tf_es = regs->r_es;
		tp->tf_fs = regs->r_fs;
		tp->tf_gs = regs->r_gs;
		tp->tf_flags = TF_HASSEGS;
	}
	set_pcb_flags(td->td_pcb, PCB_FULL_IRET);
	return (0);
}