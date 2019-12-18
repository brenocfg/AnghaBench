#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  in_nmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGABRT ; 
 int TRAP (struct pt_regs*) ; 
 int /*<<< orphan*/  die (char*,struct pt_regs*,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_paca () ; 
 int /*<<< orphan*/  machine_check_exception (struct pt_regs*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  system_reset_exception (struct pt_regs*) ; 

void kvmppc_bad_interrupt(struct pt_regs *regs)
{
	/*
	 * 100 could happen at any time, 200 can happen due to invalid real
	 * address access for example (or any time due to a hardware problem).
	 */
	if (TRAP(regs) == 0x100) {
		get_paca()->in_nmi++;
		system_reset_exception(regs);
		get_paca()->in_nmi--;
	} else if (TRAP(regs) == 0x200) {
		machine_check_exception(regs);
	} else {
		die("Bad interrupt in KVM entry/exit code", regs, SIGABRT);
	}
	panic("Bad KVM trap");
}