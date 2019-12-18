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
struct unwind_state {int /*<<< orphan*/  stack_info; int /*<<< orphan*/  stack_mask; struct task_struct* task; int /*<<< orphan*/  sp; } ;
struct task_struct {int dummy; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_ALIGN (unsigned long*,int) ; 
 int /*<<< orphan*/  __kernel_text_address (unsigned long) ; 
 int /*<<< orphan*/  get_stack_info (unsigned long*,struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct unwind_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_stack (int /*<<< orphan*/ *,unsigned long*,int) ; 
 int /*<<< orphan*/  unwind_done (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_next_frame (struct unwind_state*) ; 

void __unwind_start(struct unwind_state *state, struct task_struct *task,
		    struct pt_regs *regs, unsigned long *first_frame)
{
	memset(state, 0, sizeof(*state));

	state->task = task;
	state->sp   = PTR_ALIGN(first_frame, sizeof(long));

	get_stack_info(first_frame, state->task, &state->stack_info,
		       &state->stack_mask);

	/*
	 * The caller can provide the address of the first frame directly
	 * (first_frame) or indirectly (regs->sp) to indicate which stack frame
	 * to start unwinding at.  Skip ahead until we reach it.
	 */
	if (!unwind_done(state) &&
	    (!on_stack(&state->stack_info, first_frame, sizeof(long)) ||
	    !__kernel_text_address(*first_frame)))
		unwind_next_frame(state);
}