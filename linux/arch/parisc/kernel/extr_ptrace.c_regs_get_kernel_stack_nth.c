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
 scalar_t__ kernel_stack_pointer (struct pt_regs*) ; 
 int /*<<< orphan*/  regs_within_kernel_stack (struct pt_regs*,unsigned long) ; 

unsigned long regs_get_kernel_stack_nth(struct pt_regs *regs, unsigned int n)
{
	unsigned long *addr = (unsigned long *)kernel_stack_pointer(regs);

	addr -= n;

	if (!regs_within_kernel_stack(regs, (unsigned long)addr))
		return 0;

	return *addr;
}