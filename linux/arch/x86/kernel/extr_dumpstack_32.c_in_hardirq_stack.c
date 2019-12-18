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
 int /*<<< orphan*/  STACK_TYPE_IRQ ; 
 int THREAD_SIZE ; 
 int /*<<< orphan*/  hardirq_stack_ptr ; 
 scalar_t__ this_cpu_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool in_hardirq_stack(unsigned long *stack, struct stack_info *info)
{
	unsigned long *begin = (unsigned long *)this_cpu_read(hardirq_stack_ptr);
	unsigned long *end   = begin + (THREAD_SIZE / sizeof(long));

	/*
	 * This is a software stack, so 'end' can be a valid stack pointer.
	 * It just means the stack is empty.
	 */
	if (stack < begin || stack > end)
		return false;

	info->type	= STACK_TYPE_IRQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * See irq_32.c -- the next stack pointer is stored at the beginning of
	 * the stack.
	 */
	info->next_sp	= (unsigned long *)*begin;

	return true;
}