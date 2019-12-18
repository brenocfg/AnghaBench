#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  type; } ;
struct unwind_state {unsigned long sp; int full_regs; int signal; TYPE_2__ stack_info; int /*<<< orphan*/  stack_mask; struct task_struct* task; void* ip; void* bp; struct pt_regs* regs; } ;
struct TYPE_4__ {unsigned long sp; } ;
struct task_struct {TYPE_1__ thread; } ;
struct pt_regs {unsigned long sp; void* bp; void* ip; } ;
struct inactive_task_frame {int /*<<< orphan*/  ret_addr; int /*<<< orphan*/  bp; } ;

/* Variables and functions */
 scalar_t__ PAGE_ALIGN (unsigned long) ; 
 void* READ_ONCE_NOCHECK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STACK_TYPE_UNKNOWN ; 
 struct task_struct* current ; 
 scalar_t__ get_stack_info (void*,struct task_struct*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct unwind_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_stack (TYPE_2__*,unsigned long*,int) ; 
 scalar_t__ task_on_another_cpu (struct task_struct*) ; 
 int /*<<< orphan*/  unwind_done (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_next_frame (struct unwind_state*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void __unwind_start(struct unwind_state *state, struct task_struct *task,
		    struct pt_regs *regs, unsigned long *first_frame)
{
	memset(state, 0, sizeof(*state));
	state->task = task;

	/*
	 * Refuse to unwind the stack of a task while it's executing on another
	 * CPU.  This check is racy, but that's ok: the unwinder has other
	 * checks to prevent it from going off the rails.
	 */
	if (task_on_another_cpu(task))
		goto done;

	if (regs) {
		if (user_mode(regs))
			goto done;

		state->ip = regs->ip;
		state->sp = regs->sp;
		state->bp = regs->bp;
		state->regs = regs;
		state->full_regs = true;
		state->signal = true;

	} else if (task == current) {
		asm volatile("lea (%%rip), %0\n\t"
			     "mov %%rsp, %1\n\t"
			     "mov %%rbp, %2\n\t"
			     : "=r" (state->ip), "=r" (state->sp),
			       "=r" (state->bp));

	} else {
		struct inactive_task_frame *frame = (void *)task->thread.sp;

		state->sp = task->thread.sp;
		state->bp = READ_ONCE_NOCHECK(frame->bp);
		state->ip = READ_ONCE_NOCHECK(frame->ret_addr);
	}

	if (get_stack_info((unsigned long *)state->sp, state->task,
			   &state->stack_info, &state->stack_mask)) {
		/*
		 * We weren't on a valid stack.  It's possible that
		 * we overflowed a valid stack into a guard page.
		 * See if the next page up is valid so that we can
		 * generate some kind of backtrace if this happens.
		 */
		void *next_page = (void *)PAGE_ALIGN((unsigned long)state->sp);
		if (get_stack_info(next_page, state->task, &state->stack_info,
				   &state->stack_mask))
			return;
	}

	/*
	 * The caller can provide the address of the first frame directly
	 * (first_frame) or indirectly (regs->sp) to indicate which stack frame
	 * to start unwinding at.  Skip ahead until we reach it.
	 */

	/* When starting from regs, skip the regs frame: */
	if (regs) {
		unwind_next_frame(state);
		return;
	}

	/* Otherwise, skip ahead to the user-specified starting frame: */
	while (!unwind_done(state) &&
	       (!on_stack(&state->stack_info, first_frame, sizeof(long)) ||
			state->sp <= (unsigned long)first_frame))
		unwind_next_frame(state);

	return;

done:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	return;
}