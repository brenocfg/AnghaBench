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
typedef  enum ctx_state { ____Placeholder_ctx_state } ctx_state ;

/* Variables and functions */
 int __do_page_fault (struct pt_regs*,unsigned long,unsigned long) ; 
 int exception_enter () ; 
 int /*<<< orphan*/  exception_exit (int) ; 

int do_page_fault(struct pt_regs *regs, unsigned long address,
		  unsigned long error_code)
{
	enum ctx_state prev_state = exception_enter();
	int rc = __do_page_fault(regs, address, error_code);
	exception_exit(prev_state);
	return rc;
}