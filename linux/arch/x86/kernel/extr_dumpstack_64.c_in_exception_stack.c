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
struct pt_regs {scalar_t__ sp; } ;
struct estack_pages {int /*<<< orphan*/  type; scalar_t__ size; scalar_t__ offs; } ;
struct cea_exception_stacks {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int N_EXCEPTION_STACKS ; 
 unsigned long PAGE_SHIFT ; 
 scalar_t__ __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cea_exception_stacks ; 
 struct estack_pages* estack_pages ; 

__attribute__((used)) static bool in_exception_stack(unsigned long *stack, struct stack_info *info)
{
	unsigned long begin, end, stk = (unsigned long)stack;
	const struct estack_pages *ep;
	struct pt_regs *regs;
	unsigned int k;

	BUILD_BUG_ON(N_EXCEPTION_STACKS != 6);

	begin = (unsigned long)__this_cpu_read(cea_exception_stacks);
	/*
	 * Handle the case where stack trace is collected _before_
	 * cea_exception_stacks had been initialized.
	 */
	if (!begin)
		return false;

	end = begin + sizeof(struct cea_exception_stacks);
	/* Bail if @stack is outside the exception stack area. */
	if (stk < begin || stk >= end)
		return false;

	/* Calc page offset from start of exception stacks */
	k = (stk - begin) >> PAGE_SHIFT;
	/* Lookup the page descriptor */
	ep = &estack_pages[k];
	/* Guard page? */
	if (!ep->size)
		return false;

	begin += (unsigned long)ep->offs;
	end = begin + (unsigned long)ep->size;
	regs = (struct pt_regs *)end - 1;

	info->type	= ep->type;
	info->begin	= (unsigned long *)begin;
	info->end	= (unsigned long *)end;
	info->next_sp	= (unsigned long *)regs->sp;
	return true;
}