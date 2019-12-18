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
 int SIGSEGV ; 
 int /*<<< orphan*/  _exception (int,struct pt_regs*,int,unsigned long) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static int
__bad_area_nosemaphore(struct pt_regs *regs, unsigned long address, int si_code)
{
	/*
	 * If we are in kernel mode, bail out with a SEGV, this will
	 * be caught by the assembly which will restore the non-volatile
	 * registers before calling bad_page_fault()
	 */
	if (!user_mode(regs))
		return SIGSEGV;

	_exception(SIGSEGV, regs, si_code, address);

	return 0;
}