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
 int /*<<< orphan*/  BUG () ; 
 long EFAULT ; 
 long EINVAL ; 
 int /*<<< orphan*/  SEGV_BNDERR ; 
 int /*<<< orphan*/  SIGSEGV ; 
 int /*<<< orphan*/  _exception (int /*<<< orphan*/ ,struct pt_regs*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  bad_page_fault (struct pt_regs*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unrecoverable_exception (struct pt_regs*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void do_bad_slb_fault(struct pt_regs *regs, unsigned long ea, long err)
{
	if (err == -EFAULT) {
		if (user_mode(regs))
			_exception(SIGSEGV, regs, SEGV_BNDERR, ea);
		else
			bad_page_fault(regs, ea, SIGSEGV);
	} else if (err == -EINVAL) {
		unrecoverable_exception(regs);
	} else {
		BUG();
	}
}