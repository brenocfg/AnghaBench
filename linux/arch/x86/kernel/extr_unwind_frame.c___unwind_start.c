#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  type; } ;
struct unwind_state {unsigned long* next_bp; unsigned long* bp; TYPE_1__ stack_info; int /*<<< orphan*/  stack_mask; struct task_struct* task; struct pt_regs* got_irq; } ;
struct task_struct {int dummy; } ;
struct pt_regs {scalar_t__ ip; scalar_t__ sp; } ;

/* Variables and functions */
 int /*<<< orphan*/  STACK_TYPE_UNKNOWN ; 
 unsigned long* get_frame_pointer (struct task_struct*,struct pt_regs*) ; 
 int /*<<< orphan*/  get_stack_info (unsigned long*,struct task_struct*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct unwind_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_stack (TYPE_1__*,unsigned long*,int) ; 
 int /*<<< orphan*/  unwind_done (struct unwind_state*) ; 
 int /*<<< orphan*/  unwind_next_frame (struct unwind_state*) ; 
 int /*<<< orphan*/  update_stack_state (struct unwind_state*,unsigned long*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void __unwind_start(struct unwind_state *state, struct task_struct *task,
		    struct pt_regs *regs, unsigned long *first_frame)
{
	unsigned long *bp;

	memset(state, 0, sizeof(*state));
	state->task = task;
	state->got_irq = (regs);

	/* Don't even attempt to start from user mode regs: */
	if (regs && user_mode(regs)) {
		state->stack_info.type = STACK_TYPE_UNKNOWN;
		return;
	}

	bp = get_frame_pointer(task, regs);

	/*
	 * If we crash with IP==0, the last successfully executed instruction
	 * was probably an indirect function call with a NULL function pointer.
	 * That means that SP points into the middle of an incomplete frame:
	 * *SP is a return pointer, and *(SP-sizeof(unsigned long)) is where we
	 * would have written a frame pointer if we hadn't crashed.
	 * Pretend that the frame is complete and that BP points to it, but save
	 * the real BP so that we can use it when looking for the next frame.
	 */
	if (regs && regs->ip == 0 && (unsigned long *)regs->sp >= first_frame) {
		state->next_bp = bp;
		bp = ((unsigned long *)regs->sp) - 1;
	}

	/* Initialize stack info and make sure the frame data is accessible: */
	get_stack_info(bp, state->task, &state->stack_info,
		       &state->stack_mask);
	update_stack_state(state, bp);

	/*
	 * The caller can provide the address of the first frame directly
	 * (first_frame) or indirectly (regs->sp) to indicate which stack frame
	 * to start unwinding at.  Skip ahead until we reach it.
	 */
	while (!unwind_done(state) &&
	       (!on_stack(&state->stack_info, first_frame, sizeof(long)) ||
			(state->next_bp == NULL && state->bp < first_frame)))
		unwind_next_frame(state);
}