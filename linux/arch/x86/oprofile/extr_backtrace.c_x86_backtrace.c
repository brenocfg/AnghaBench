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
struct unwind_state {int dummy; } ;
struct stack_frame {int dummy; } ;
struct pt_regs {unsigned long ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  current ; 
 struct stack_frame* dump_user_backtrace (struct stack_frame*) ; 
 scalar_t__ frame_pointer (struct pt_regs* const) ; 
 int /*<<< orphan*/  oprofile_add_trace (unsigned long) ; 
 int /*<<< orphan*/  unwind_done (struct unwind_state*) ; 
 unsigned long unwind_get_return_address (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_next_frame (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_start (struct unwind_state*,int /*<<< orphan*/ ,struct pt_regs* const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  user_mode (struct pt_regs* const) ; 
 scalar_t__ x86_backtrace_32 (struct pt_regs* const,unsigned int) ; 

void
x86_backtrace(struct pt_regs * const regs, unsigned int depth)
{
	struct stack_frame *head = (struct stack_frame *)frame_pointer(regs);

	if (!user_mode(regs)) {
		struct unwind_state state;
		unsigned long addr;

		if (!depth)
			return;

		oprofile_add_trace(regs->ip);

		if (!--depth)
			return;

		for (unwind_start(&state, current, regs, NULL);
		     !unwind_done(&state); unwind_next_frame(&state)) {
			addr = unwind_get_return_address(&state);
			if (!addr)
				break;

			oprofile_add_trace(addr);

			if (!--depth)
				break;
		}

		return;
	}

	if (x86_backtrace_32(regs, depth))
		return;

	while (depth-- && head)
		head = dump_user_backtrace(head);
}