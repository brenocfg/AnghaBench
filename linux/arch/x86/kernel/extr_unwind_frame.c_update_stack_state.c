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
struct stack_info {int type; int /*<<< orphan*/  next_sp; } ;
struct unwind_state {unsigned long* bp; int got_irq; unsigned long* orig_sp; int /*<<< orphan*/  graph_idx; int /*<<< orphan*/  task; int /*<<< orphan*/  ip; struct pt_regs* regs; struct stack_info stack_info; int /*<<< orphan*/  stack_mask; } ;
struct pt_regs {int dummy; } ;
typedef  enum stack_type { ____Placeholder_stack_type } stack_type ;

/* Variables and functions */
 size_t FRAME_HEADER_SIZE ; 
 unsigned long READ_ONCE_TASK_STACK (int /*<<< orphan*/ ,unsigned long) ; 
 struct pt_regs* decode_frame_pointer (unsigned long*) ; 
 int /*<<< orphan*/  ftrace_graph_ret_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,unsigned long*) ; 
 scalar_t__ get_stack_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct stack_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_stack (struct stack_info*,unsigned long*,size_t) ; 
 unsigned long* unwind_get_return_address_ptr (struct unwind_state*) ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

__attribute__((used)) static bool update_stack_state(struct unwind_state *state,
			       unsigned long *next_bp)
{
	struct stack_info *info = &state->stack_info;
	enum stack_type prev_type = info->type;
	struct pt_regs *regs;
	unsigned long *frame, *prev_frame_end, *addr_p, addr;
	size_t len;

	if (state->regs)
		prev_frame_end = (void *)state->regs + sizeof(*state->regs);
	else
		prev_frame_end = (void *)state->bp + FRAME_HEADER_SIZE;

	/* Is the next frame pointer an encoded pointer to pt_regs? */
	regs = decode_frame_pointer(next_bp);
	if (regs) {
		frame = (unsigned long *)regs;
		len = sizeof(*regs);
		state->got_irq = true;
	} else {
		frame = next_bp;
		len = FRAME_HEADER_SIZE;
	}

	/*
	 * If the next bp isn't on the current stack, switch to the next one.
	 *
	 * We may have to traverse multiple stacks to deal with the possibility
	 * that info->next_sp could point to an empty stack and the next bp
	 * could be on a subsequent stack.
	 */
	while (!on_stack(info, frame, len))
		if (get_stack_info(info->next_sp, state->task, info,
				   &state->stack_mask))
			return false;

	/* Make sure it only unwinds up and doesn't overlap the prev frame: */
	if (state->orig_sp && state->stack_info.type == prev_type &&
	    frame < prev_frame_end)
		return false;

	/* Move state to the next frame: */
	if (regs) {
		state->regs = regs;
		state->bp = NULL;
	} else {
		state->bp = next_bp;
		state->regs = NULL;
	}

	/* Save the return address: */
	if (state->regs && user_mode(state->regs))
		state->ip = 0;
	else {
		addr_p = unwind_get_return_address_ptr(state);
		addr = READ_ONCE_TASK_STACK(state->task, *addr_p);
		state->ip = ftrace_graph_ret_addr(state->task, &state->graph_idx,
						  addr, addr_p);
	}

	/* Save the original stack pointer for unwind_dump(): */
	if (!state->orig_sp)
		state->orig_sp = frame;

	return true;
}