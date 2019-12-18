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
struct stack_info {unsigned long* begin; unsigned long* end; unsigned long* next_sp; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int IRQ_STACK_SIZE ; 
 int /*<<< orphan*/  STACK_TYPE_IRQ ; 
 int /*<<< orphan*/  hardirq_stack_ptr ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool in_irq_stack(unsigned long *stack, struct stack_info *info)
{
	unsigned long *end   = (unsigned long *)this_cpu_read(hardirq_stack_ptr);
	unsigned long *begin = end - (IRQ_STACK_SIZE / sizeof(long));

	/*
	 * This is a software stack, so 'end' can be a valid stack pointer.
	 * It just means the stack is empty.
	 */
	if (stack < begin || stack >= end)
		return false;

	info->type	= STACK_TYPE_IRQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * The next stack pointer is the first thing pushed by the entry code
	 * after switching to the irq stack.
	 */
	info->next_sp = (unsigned long *)*(end - 1);

	return true;
}