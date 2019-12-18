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
 scalar_t__ __copy_from_user_inatomic (unsigned long*,unsigned long*,int) ; 
 int /*<<< orphan*/  access_ok (unsigned long*,int) ; 
 int /*<<< orphan*/  oprofile_add_trace (unsigned long) ; 

__attribute__((used)) static unsigned long *
user_backtrace(unsigned long *stackaddr, struct pt_regs *regs)
{
	unsigned long buf_stack;

	/* Also check accessibility of address */
	if (!access_ok(stackaddr, sizeof(unsigned long)))
		return NULL;

	if (__copy_from_user_inatomic(&buf_stack, stackaddr, sizeof(unsigned long)))
		return NULL;

	/* Quick paranoia check */
	if (buf_stack & 3)
		return NULL;

	oprofile_add_trace(buf_stack);

	stackaddr++;

	return stackaddr;
}