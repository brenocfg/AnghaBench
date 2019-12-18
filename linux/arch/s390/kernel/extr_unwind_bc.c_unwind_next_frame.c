#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stack_info {int /*<<< orphan*/  type; } ;
struct unwind_state {int reuse_sp; unsigned long sp; unsigned long ip; int reliable; int error; struct stack_info stack_info; struct pt_regs* regs; int /*<<< orphan*/  graph_idx; int /*<<< orphan*/  task; } ;
struct stack_frame {int /*<<< orphan*/ * gprs; int /*<<< orphan*/  back_chain; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; int /*<<< orphan*/  mask; } ;
struct pt_regs {TYPE_1__ psw; int /*<<< orphan*/ * gprs; } ;

/* Variables and functions */
 int PSW_MASK_PSTATE ; 
 int READ_ONCE_NOCHECK (int /*<<< orphan*/ ) ; 
 unsigned long STACK_FRAME_OVERHEAD ; 
 int /*<<< orphan*/  STACK_TYPE_UNKNOWN ; 
 unsigned long ftrace_graph_ret_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long,void*) ; 
 scalar_t__ likely (unsigned long) ; 
 int /*<<< orphan*/  on_stack (struct stack_info*,unsigned long,int) ; 
 struct pt_regs* outside_of_stack (struct unwind_state*,unsigned long) ; 
 scalar_t__ return_to_handler ; 
 scalar_t__ unlikely (struct pt_regs*) ; 
 int /*<<< orphan*/  update_stack_info (struct unwind_state*,unsigned long) ; 

bool unwind_next_frame(struct unwind_state *state)
{
	struct stack_info *info = &state->stack_info;
	struct stack_frame *sf;
	struct pt_regs *regs;
	unsigned long sp, ip;
	bool reliable;

	regs = state->regs;
	if (unlikely(regs)) {
		if (state->reuse_sp) {
			sp = state->sp;
			state->reuse_sp = false;
		} else {
			sp = READ_ONCE_NOCHECK(regs->gprs[15]);
			if (unlikely(outside_of_stack(state, sp))) {
				if (!update_stack_info(state, sp))
					goto out_err;
			}
		}
		sf = (struct stack_frame *) sp;
		ip = READ_ONCE_NOCHECK(sf->gprs[8]);
		reliable = false;
		regs = NULL;
	} else {
		sf = (struct stack_frame *) state->sp;
		sp = READ_ONCE_NOCHECK(sf->back_chain);
		if (likely(sp)) {
			/* Non-zero back-chain points to the previous frame */
			if (unlikely(outside_of_stack(state, sp))) {
				if (!update_stack_info(state, sp))
					goto out_err;
			}
			sf = (struct stack_frame *) sp;
			ip = READ_ONCE_NOCHECK(sf->gprs[8]);
			reliable = true;
		} else {
			/* No back-chain, look for a pt_regs structure */
			sp = state->sp + STACK_FRAME_OVERHEAD;
			if (!on_stack(info, sp, sizeof(struct pt_regs)))
				goto out_stop;
			regs = (struct pt_regs *) sp;
			if (READ_ONCE_NOCHECK(regs->psw.mask) & PSW_MASK_PSTATE)
				goto out_stop;
			ip = READ_ONCE_NOCHECK(regs->psw.addr);
			reliable = true;
		}
	}

#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	/* Decode any ftrace redirection */
	if (ip == (unsigned long) return_to_handler)
		ip = ftrace_graph_ret_addr(state->task, &state->graph_idx,
					   ip, (void *) sp);
#endif

	/* Update unwind state */
	state->sp = sp;
	state->ip = ip;
	state->regs = regs;
	state->reliable = reliable;
	return true;

out_err:
	state->error = true;
out_stop:
	state->stack_info.type = STACK_TYPE_UNKNOWN;
	return false;
}