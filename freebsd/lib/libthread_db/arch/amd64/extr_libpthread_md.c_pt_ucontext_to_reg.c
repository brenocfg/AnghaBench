#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  mc_ss; int /*<<< orphan*/  mc_rsp; int /*<<< orphan*/  mc_rflags; int /*<<< orphan*/  mc_cs; int /*<<< orphan*/  mc_rip; int /*<<< orphan*/  mc_r15; int /*<<< orphan*/  mc_r14; int /*<<< orphan*/  mc_r13; int /*<<< orphan*/  mc_r12; int /*<<< orphan*/  mc_r11; int /*<<< orphan*/  mc_r10; int /*<<< orphan*/  mc_rbp; int /*<<< orphan*/  mc_rbx; int /*<<< orphan*/  mc_rax; int /*<<< orphan*/  mc_r9; int /*<<< orphan*/  mc_r8; int /*<<< orphan*/  mc_rcx; int /*<<< orphan*/  mc_rdx; int /*<<< orphan*/  mc_rsi; int /*<<< orphan*/  mc_rdi; } ;
struct TYPE_4__ {TYPE_2__ uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct reg {int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_rsp; int /*<<< orphan*/  r_rflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_rip; int /*<<< orphan*/  r_r15; int /*<<< orphan*/  r_r14; int /*<<< orphan*/  r_r13; int /*<<< orphan*/  r_r12; int /*<<< orphan*/  r_r11; int /*<<< orphan*/  r_r10; int /*<<< orphan*/  r_rbp; int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rax; int /*<<< orphan*/  r_r9; int /*<<< orphan*/  r_r8; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdi; } ;
typedef  TYPE_2__ mcontext_t ;

/* Variables and functions */

void
pt_ucontext_to_reg(const ucontext_t *uc, struct reg *r)
{
	const mcontext_t *mc = &uc->uc_mcontext;

	r->r_rdi = mc->mc_rdi;
	r->r_rsi = mc->mc_rsi;
	r->r_rdx = mc->mc_rdx;
	r->r_rcx = mc->mc_rcx;
	r->r_r8 = mc->mc_r8;
	r->r_r9 = mc->mc_r9;
	r->r_rax = mc->mc_rax;
	r->r_rbx = mc->mc_rbx;
	r->r_rbp = mc->mc_rbp;
	r->r_r10 = mc->mc_r10;
	r->r_r11 = mc->mc_r11;
	r->r_r12 = mc->mc_r12;
	r->r_r13 = mc->mc_r13;
	r->r_r14 = mc->mc_r14;
	r->r_r15 = mc->mc_r15;
	r->r_rip = mc->mc_rip;
	r->r_cs = mc->mc_cs;
	r->r_rflags = mc->mc_rflags;
	r->r_rsp = mc->mc_rsp;
	r->r_ss = mc->mc_ss;
}