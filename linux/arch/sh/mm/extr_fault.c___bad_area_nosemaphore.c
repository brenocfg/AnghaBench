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
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  force_sig_info_fault (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  no_context (struct pt_regs*,unsigned long,unsigned long) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static void
__bad_area_nosemaphore(struct pt_regs *regs, unsigned long error_code,
		       unsigned long address, int si_code)
{
	/* User mode accesses just cause a SIGSEGV */
	if (user_mode(regs)) {
		/*
		 * It's possible to have interrupts off here:
		 */
		local_irq_enable();

		force_sig_info_fault(SIGSEGV, si_code, address);

		return;
	}

	no_context(regs, error_code, address);
}