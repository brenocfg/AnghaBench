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
 int /*<<< orphan*/  _exception_pkey (struct pt_regs*,unsigned long,int) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs*) ; 

__attribute__((used)) static int bad_key_fault_exception(struct pt_regs *regs, unsigned long address,
				    int pkey)
{
	/*
	 * If we are in kernel mode, bail out with a SEGV, this will
	 * be caught by the assembly which will restore the non-volatile
	 * registers before calling bad_page_fault()
	 */
	if (!user_mode(regs))
		return SIGSEGV;

	_exception_pkey(regs, address, pkey);

	return 0;
}