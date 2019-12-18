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
struct stack_info {int /*<<< orphan*/ * next_sp; void* end; void* begin; int /*<<< orphan*/  type; } ;
struct entry_stack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_TYPE_ENTRY ; 
 struct entry_stack* cpu_entry_stack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

bool in_entry_stack(unsigned long *stack, struct stack_info *info)
{
	struct entry_stack *ss = cpu_entry_stack(smp_processor_id());

	void *begin = ss;
	void *end = ss + 1;

	if ((void *)stack < begin || (void *)stack >= end)
		return false;

	info->type	= STACK_TYPE_ENTRY;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= NULL;

	return true;
}