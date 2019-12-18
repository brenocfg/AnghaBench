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
struct reg {int /*<<< orphan*/  r_ss; int /*<<< orphan*/  r_esp; int /*<<< orphan*/  r_eflags; int /*<<< orphan*/  r_cs; int /*<<< orphan*/  r_eip; int /*<<< orphan*/  r_eax; int /*<<< orphan*/  r_gs; int /*<<< orphan*/  r_fs; int /*<<< orphan*/  r_es; int /*<<< orphan*/  r_ds; int /*<<< orphan*/  r_ebp; int /*<<< orphan*/  r_edi; int /*<<< orphan*/  r_esi; int /*<<< orphan*/  r_edx; int /*<<< orphan*/  r_ecx; int /*<<< orphan*/  r_ebx; } ;
struct linux_pt_reg {int /*<<< orphan*/  xss; int /*<<< orphan*/  esp; int /*<<< orphan*/  eflags; int /*<<< orphan*/  xcs; int /*<<< orphan*/  eip; int /*<<< orphan*/  orig_eax; int /*<<< orphan*/  xgs; int /*<<< orphan*/  xfs; int /*<<< orphan*/  xes; int /*<<< orphan*/  xds; int /*<<< orphan*/  eax; int /*<<< orphan*/  ebp; int /*<<< orphan*/  edi; int /*<<< orphan*/  esi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; } ;

/* Variables and functions */

__attribute__((used)) static void
map_regs_to_linux(struct reg *bsd_r, struct linux_pt_reg *linux_r)
{
	linux_r->ebx = bsd_r->r_ebx;
	linux_r->ecx = bsd_r->r_ecx;
	linux_r->edx = bsd_r->r_edx;
	linux_r->esi = bsd_r->r_esi;
	linux_r->edi = bsd_r->r_edi;
	linux_r->ebp = bsd_r->r_ebp;
	linux_r->eax = bsd_r->r_eax;
	linux_r->xds = bsd_r->r_ds;
	linux_r->xes = bsd_r->r_es;
	linux_r->xfs = bsd_r->r_fs;
	linux_r->xgs = bsd_r->r_gs;
	linux_r->orig_eax = bsd_r->r_eax;
	linux_r->eip = bsd_r->r_eip;
	linux_r->xcs = bsd_r->r_cs;
	linux_r->eflags = bsd_r->r_eflags;
	linux_r->esp = bsd_r->r_esp;
	linux_r->xss = bsd_r->r_ss;
}