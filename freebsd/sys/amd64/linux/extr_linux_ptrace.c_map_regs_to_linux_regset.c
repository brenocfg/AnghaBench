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
struct reg {int /*<<< orphan*/  r_gs; int /*<<< orphan*/  r_fs; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_rsp; int /*<<< orphan*/  r_rflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_rip; int /*<<< orphan*/  r_rax; int /*<<< orphan*/  r_rdi; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r10; int /*<<< orphan*/  r_r11; int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rbp; int /*<<< orphan*/  r_r12; int /*<<< orphan*/  r_r13; int /*<<< orphan*/  r_r14; int /*<<< orphan*/  r_r15; } ;
struct linux_pt_regset {unsigned long fs_base; unsigned long gs_base; int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  es; int /*<<< orphan*/  ds; int /*<<< orphan*/  ss; int /*<<< orphan*/  rsp; int /*<<< orphan*/  eflags; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  orig_rax; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rax; int /*<<< orphan*/  r8; int /*<<< orphan*/  r9; int /*<<< orphan*/  r10; int /*<<< orphan*/  r11; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rbp; int /*<<< orphan*/  r12; int /*<<< orphan*/  r13; int /*<<< orphan*/  r14; int /*<<< orphan*/  r15; } ;

/* Variables and functions */

__attribute__((used)) static void
map_regs_to_linux_regset(struct reg *b_reg, unsigned long fs_base,
    unsigned long gs_base, struct linux_pt_regset *l_regset)
{

	l_regset->r15 = b_reg->r_r15;
	l_regset->r14 = b_reg->r_r14;
	l_regset->r13 = b_reg->r_r13;
	l_regset->r12 = b_reg->r_r12;
	l_regset->rbp = b_reg->r_rbp;
	l_regset->rbx = b_reg->r_rbx;
	l_regset->r11 = b_reg->r_r11;
	l_regset->r10 = b_reg->r_r10;
	l_regset->r9 = b_reg->r_r9;
	l_regset->r8 = b_reg->r_r8;
	l_regset->rax = b_reg->r_rax;
	l_regset->rcx = b_reg->r_rcx;
	l_regset->rdx = b_reg->r_rdx;
	l_regset->rsi = b_reg->r_rsi;
	l_regset->rdi = b_reg->r_rdi;
	l_regset->orig_rax = b_reg->r_rax;
	l_regset->rip = b_reg->r_rip;
	l_regset->cs = b_reg->r_cs;
	l_regset->eflags = b_reg->r_rflags;
	l_regset->rsp = b_reg->r_rsp;
	l_regset->ss = b_reg->r_ss;
	l_regset->fs_base = fs_base;
	l_regset->gs_base = gs_base;
	l_regset->ds = b_reg->r_ds;
	l_regset->es = b_reg->r_es;
	l_regset->fs = b_reg->r_fs;
	l_regset->gs = b_reg->r_gs;
}