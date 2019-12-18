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
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct pt_regs {TYPE_2__ psw; } ;
struct arch_uprobe {int /*<<< orphan*/  insn; } ;
struct TYPE_4__ {scalar_t__ eaba; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILL_ILLADR ; 
 scalar_t__ PSW_BITS_AMODE_24BIT ; 
 scalar_t__ PSW_BITS_AMODE_31BIT ; 
 int /*<<< orphan*/  SIGILL ; 
 int /*<<< orphan*/  UPROBE_SWBP_INSN_SIZE ; 
 int /*<<< orphan*/  __rewind_psw (TYPE_2__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_report_trap (struct pt_regs*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_insn_ril (struct arch_uprobe*,struct pt_regs*) ; 
 int /*<<< orphan*/  is_compat_task () ; 
 scalar_t__ probe_is_insn_relative_long (int /*<<< orphan*/ ) ; 
 TYPE_1__ psw_bits (TYPE_2__) ; 

bool arch_uprobe_skip_sstep(struct arch_uprobe *auprobe, struct pt_regs *regs)
{
	if ((psw_bits(regs->psw).eaba == PSW_BITS_AMODE_24BIT) ||
	    ((psw_bits(regs->psw).eaba == PSW_BITS_AMODE_31BIT) &&
	     !is_compat_task())) {
		regs->psw.addr = __rewind_psw(regs->psw, UPROBE_SWBP_INSN_SIZE);
		do_report_trap(regs, SIGILL, ILL_ILLADR, NULL);
		return true;
	}
	if (probe_is_insn_relative_long(auprobe->insn)) {
		handle_insn_ril(auprobe, regs);
		return true;
	}
	return false;
}