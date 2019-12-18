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
struct trapframe {int tf_flags; scalar_t__ tf_gs; scalar_t__ tf_fs; scalar_t__ tf_es; scalar_t__ tf_ds; int /*<<< orphan*/  tf_ss; int /*<<< orphan*/  tf_rsp; int /*<<< orphan*/  tf_rflags; int /*<<< orphan*/  tf_cs; int /*<<< orphan*/  tf_rip; int /*<<< orphan*/  tf_rax; int /*<<< orphan*/  tf_rcx; int /*<<< orphan*/  tf_rdx; int /*<<< orphan*/  tf_rbx; int /*<<< orphan*/  tf_rbp; int /*<<< orphan*/  tf_rsi; int /*<<< orphan*/  tf_rdi; int /*<<< orphan*/  tf_r8; int /*<<< orphan*/  tf_r9; int /*<<< orphan*/  tf_r10; int /*<<< orphan*/  tf_r11; int /*<<< orphan*/  tf_r12; int /*<<< orphan*/  tf_r13; int /*<<< orphan*/  tf_r14; int /*<<< orphan*/  tf_r15; } ;
struct reg {scalar_t__ r_trapno; scalar_t__ r_err; scalar_t__ r_gs; scalar_t__ r_fs; scalar_t__ r_es; scalar_t__ r_ds; int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_rsp; int /*<<< orphan*/  r_rflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_rip; int /*<<< orphan*/  r_rax; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rbp; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdi; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r10; int /*<<< orphan*/  r_r11; int /*<<< orphan*/  r_r12; int /*<<< orphan*/  r_r13; int /*<<< orphan*/  r_r14; int /*<<< orphan*/  r_r15; } ;

/* Variables and functions */
 int TF_HASSEGS ; 

int
fill_frame_regs(struct trapframe *tp, struct reg *regs)
{

	regs->r_r15 = tp->tf_r15;
	regs->r_r14 = tp->tf_r14;
	regs->r_r13 = tp->tf_r13;
	regs->r_r12 = tp->tf_r12;
	regs->r_r11 = tp->tf_r11;
	regs->r_r10 = tp->tf_r10;
	regs->r_r9  = tp->tf_r9;
	regs->r_r8  = tp->tf_r8;
	regs->r_rdi = tp->tf_rdi;
	regs->r_rsi = tp->tf_rsi;
	regs->r_rbp = tp->tf_rbp;
	regs->r_rbx = tp->tf_rbx;
	regs->r_rdx = tp->tf_rdx;
	regs->r_rcx = tp->tf_rcx;
	regs->r_rax = tp->tf_rax;
	regs->r_rip = tp->tf_rip;
	regs->r_cs = tp->tf_cs;
	regs->r_rflags = tp->tf_rflags;
	regs->r_rsp = tp->tf_rsp;
	regs->r_ss = tp->tf_ss;
	if (tp->tf_flags & TF_HASSEGS) {
		regs->r_ds = tp->tf_ds;
		regs->r_es = tp->tf_es;
		regs->r_fs = tp->tf_fs;
		regs->r_gs = tp->tf_gs;
	} else {
		regs->r_ds = 0;
		regs->r_es = 0;
		regs->r_fs = 0;
		regs->r_gs = 0;
	}
	regs->r_err = 0;
	regs->r_trapno = 0;
	return (0);
}