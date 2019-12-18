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
struct stack_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_TYPE_TASK ; 
 scalar_t__ THREAD_SIZE ; 
 int in_stack (unsigned long,struct stack_info*,int /*<<< orphan*/ ,unsigned long,scalar_t__) ; 
 scalar_t__ task_stack_page (struct task_struct*) ; 

__attribute__((used)) static bool in_task_stack(unsigned long sp, struct task_struct *task,
			  struct stack_info *info)
{
	unsigned long stack;

	stack = (unsigned long) task_stack_page(task);
	return in_stack(sp, info, STACK_TYPE_TASK, stack, stack + THREAD_SIZE);
}