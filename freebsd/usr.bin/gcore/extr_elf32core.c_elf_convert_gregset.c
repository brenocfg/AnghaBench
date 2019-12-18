#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct reg {int /*<<< orphan*/  pc; int /*<<< orphan*/  ctr; int /*<<< orphan*/  xer; int /*<<< orphan*/  cr; int /*<<< orphan*/  lr; int /*<<< orphan*/ * fixreg; int /*<<< orphan*/  spsr; int /*<<< orphan*/  elr; int /*<<< orphan*/ * x; int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_rsp; int /*<<< orphan*/  r_rflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_rip; int /*<<< orphan*/  r_rax; int /*<<< orphan*/  r_rcx; int /*<<< orphan*/  r_rdx; int /*<<< orphan*/  r_rbx; int /*<<< orphan*/  r_rbp; int /*<<< orphan*/  r_rsi; int /*<<< orphan*/  r_rdi; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_fs; int /*<<< orphan*/  r_gs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pc; int /*<<< orphan*/  ctr; int /*<<< orphan*/  xer; int /*<<< orphan*/  cr; int /*<<< orphan*/  lr; int /*<<< orphan*/ * fixreg; int /*<<< orphan*/  r_cpsr; int /*<<< orphan*/  r_pc; int /*<<< orphan*/  r_lr; int /*<<< orphan*/  r_sp; int /*<<< orphan*/ * r; int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_esp; int /*<<< orphan*/  r_eflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_eip; int /*<<< orphan*/  r_eax; int /*<<< orphan*/  r_ecx; int /*<<< orphan*/  r_edx; int /*<<< orphan*/  r_ebx; int /*<<< orphan*/  r_ebp; int /*<<< orphan*/  r_esi; int /*<<< orphan*/  r_edi; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_fs; int /*<<< orphan*/  r_gs; } ;
typedef  TYPE_1__ elfcore_gregset_t ;

/* Variables and functions */

__attribute__((used)) static void
elf_convert_gregset(elfcore_gregset_t *rd, struct reg *rs)
{
#ifdef __amd64__
	rd->r_gs = rs->r_gs;
	rd->r_fs = rs->r_fs;
	rd->r_es = rs->r_es;
	rd->r_ds = rs->r_ds;
	rd->r_edi = rs->r_rdi;
	rd->r_esi = rs->r_rsi;
	rd->r_ebp = rs->r_rbp;
	rd->r_ebx = rs->r_rbx;
	rd->r_edx = rs->r_rdx;
	rd->r_ecx = rs->r_rcx;
	rd->r_eax = rs->r_rax;
	rd->r_eip = rs->r_rip;
	rd->r_cs = rs->r_cs;
	rd->r_eflags = rs->r_rflags;
	rd->r_esp = rs->r_rsp;
	rd->r_ss = rs->r_ss;
#elif defined(__aarch64__)
	int i;

	for (i = 0; i < 13; i++)
		rd->r[i] = rs->x[i];
	rd->r_sp = rs->x[13];
	rd->r_lr = rs->x[14];
	rd->r_pc = rs->elr;
	rd->r_cpsr = rs->spsr;
#elif defined(__powerpc64__)
	int i;

	for (i = 0; i < 32; i++)
		rd->fixreg[i] = rs->fixreg[i];
	rd->lr = rs->lr;
	rd->cr = rs->cr;
	rd->xer = rs->xer;
	rd->ctr = rs->ctr;
	rd->pc = rs->pc;
#else
#error Unsupported architecture
#endif
}