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
struct reg {int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_rsp; int /*<<< orphan*/  r_rflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_rip; int /*<<< orphan*/  r_rax; int /*<<< orphan*/  r_rdi; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r10; int /*<<< orphan*/  r_r11; int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rbp; int /*<<< orphan*/  r_r12; int /*<<< orphan*/  r_r13; int /*<<< orphan*/  r_r14; int /*<<< orphan*/  r_r15; } ;
struct linux_pt_reg {int /*<<< orphan*/  ss; int /*<<< orphan*/  rsp; int /*<<< orphan*/  eflags; int /*<<< orphan*/  cs; int /*<<< orphan*/  rip; int /*<<< orphan*/  orig_rax; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rax; int /*<<< orphan*/  r8; int /*<<< orphan*/  r9; int /*<<< orphan*/  r10; int /*<<< orphan*/  r11; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rbp; int /*<<< orphan*/  r12; int /*<<< orphan*/  r13; int /*<<< orphan*/  r14; int /*<<< orphan*/  r15; } ;

/* Variables and functions */

__attribute__((used)) static void
map_regs_to_linux(struct reg *b_reg, struct linux_pt_reg *l_reg)
{

	l_reg->r15 = b_reg->r_r15;
	l_reg->r14 = b_reg->r_r14;
	l_reg->r13 = b_reg->r_r13;
	l_reg->r12 = b_reg->r_r12;
	l_reg->rbp = b_reg->r_rbp;
	l_reg->rbx = b_reg->r_rbx;
	l_reg->r11 = b_reg->r_r11;
	l_reg->r10 = b_reg->r_r10;
	l_reg->r9 = b_reg->r_r9;
	l_reg->r8 = b_reg->r_r8;
	l_reg->rax = b_reg->r_rax;
	l_reg->rcx = b_reg->r_rcx;
	l_reg->rdx = b_reg->r_rdx;
	l_reg->rsi = b_reg->r_rsi;
	l_reg->rdi = b_reg->r_rdi;
	l_reg->orig_rax = b_reg->r_rax;
	l_reg->rip = b_reg->r_rip;
	l_reg->cs = b_reg->r_cs;
	l_reg->eflags = b_reg->r_rflags;
	l_reg->rsp = b_reg->r_rsp;
	l_reg->ss = b_reg->r_ss;
}