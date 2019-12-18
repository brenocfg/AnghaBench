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
struct pt_regs {int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  sp; int /*<<< orphan*/  bp; int /*<<< orphan*/  di; int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  ax; } ;
struct pebs_gprs {int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  sp; int /*<<< orphan*/  bp; int /*<<< orphan*/  di; int /*<<< orphan*/  si; int /*<<< orphan*/  dx; int /*<<< orphan*/  cx; int /*<<< orphan*/  bx; int /*<<< orphan*/  ax; } ;

/* Variables and functions */

__attribute__((used)) static void adaptive_pebs_save_regs(struct pt_regs *regs,
				    struct pebs_gprs *gprs)
{
	regs->ax = gprs->ax;
	regs->bx = gprs->bx;
	regs->cx = gprs->cx;
	regs->dx = gprs->dx;
	regs->si = gprs->si;
	regs->di = gprs->di;
	regs->bp = gprs->bp;
	regs->sp = gprs->sp;
#ifndef CONFIG_X86_32
	regs->r8 = gprs->r8;
	regs->r9 = gprs->r9;
	regs->r10 = gprs->r10;
	regs->r11 = gprs->r11;
	regs->r12 = gprs->r12;
	regs->r13 = gprs->r13;
	regs->r14 = gprs->r14;
	regs->r15 = gprs->r15;
#endif
}