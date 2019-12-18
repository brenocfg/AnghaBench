#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  addr; } ;
struct pt_regs {TYPE_5__ psw; int /*<<< orphan*/  int_code; } ;
struct arch_uprobe {int /*<<< orphan*/  saved_int_code; int /*<<< orphan*/  saved_per; } ;
struct TYPE_9__ {scalar_t__ eaba; int /*<<< orphan*/  per; } ;
struct TYPE_8__ {TYPE_1__* utask; } ;
struct TYPE_7__ {int /*<<< orphan*/  xol_vaddr; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  PIF_PER_TRAP ; 
 scalar_t__ PSW_BITS_AMODE_24BIT ; 
 scalar_t__ PSW_BITS_AMODE_31BIT ; 
 int /*<<< orphan*/  TIF_UPROBE_SINGLESTEP ; 
 int /*<<< orphan*/  UPROBE_TRAP_NR ; 
 int /*<<< orphan*/  clear_pt_regs_flag (struct pt_regs*,int /*<<< orphan*/ ) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  is_compat_task () ; 
 TYPE_4__ psw_bits (TYPE_5__) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_cr_regs (TYPE_2__*) ; 

int arch_uprobe_pre_xol(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	if (psw_bits(regs->psw).eaba == PSW_BITS_AMODE_24BIT)
		return -EINVAL;
	if (!is_compat_task() && psw_bits(regs->psw).eaba == PSW_BITS_AMODE_31BIT)
		return -EINVAL;
	clear_pt_regs_flag(regs, PIF_PER_TRAP);
	auprobe->saved_per = psw_bits(regs->psw).per;
	auprobe->saved_int_code = regs->int_code;
	regs->int_code = UPROBE_TRAP_NR;
	regs->psw.addr = current->utask->xol_vaddr;
	set_tsk_thread_flag(current, TIF_UPROBE_SINGLESTEP);
	update_cr_regs(current);
	return 0;
}