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
struct task_struct {int dummy; } ;
struct stack_info {unsigned long* begin; unsigned long* end; int /*<<< orphan*/ * next_sp; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_TYPE_TASK ; 
 int THREAD_SIZE ; 
 unsigned long* task_stack_page (struct task_struct*) ; 

bool in_task_stack(unsigned long *stack, struct task_struct *task,
		   struct stack_info *info)
{
	unsigned long *begin = task_stack_page(task);
	unsigned long *end   = task_stack_page(task) + THREAD_SIZE;

	if (stack < begin || stack >= end)
		return false;

	info->type	= STACK_TYPE_TASK;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= NULL;

	return true;
}