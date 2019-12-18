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
 int THREAD_SIZE ; 
 int kernel_stack_pointer (struct pt_regs*) ; 
 scalar_t__ on_irq_stack (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool regs_within_kernel_stack(struct pt_regs *regs, unsigned long addr)
{
	return ((addr & ~(THREAD_SIZE - 1))  ==
		(kernel_stack_pointer(regs) & ~(THREAD_SIZE - 1))) ||
		on_irq_stack(addr, NULL);
}