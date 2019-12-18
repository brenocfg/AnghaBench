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
struct stack_info {void* type; } ;
struct unwind_state {unsigned long stack_mask; int error; unsigned long sp; unsigned long ip; int reliable; int reuse_sp; int /*<<< orphan*/  graph_idx; struct task_struct* task; struct pt_regs* regs; struct stack_info stack_info; } ;
struct task_struct {int dummy; } ;
struct stack_frame {int /*<<< orphan*/ * gprs; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;
struct pt_regs {TYPE_1__ psw; } ;

/* Variables and functions */
 unsigned long READ_ONCE_NOCHECK (int /*<<< orphan*/ ) ; 
 void* STACK_TYPE_UNKNOWN ; 
 unsigned long ftrace_graph_ret_addr (struct task_struct*,int /*<<< orphan*/ *,unsigned long,int /*<<< orphan*/ *) ; 
 scalar_t__ get_stack_info (unsigned long,struct task_struct*,struct stack_info*,unsigned long*) ; 
 int /*<<< orphan*/  memset (struct unwind_state*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_stack (struct stack_info*,unsigned long,int) ; 
 scalar_t__ return_to_handler ; 
 scalar_t__ user_mode (struct pt_regs*) ; 

void __unwind_start(struct unwind_state *state, struct task_struct *task,
		    struct pt_regs *regs, unsigned long sp)
{
	struct stack_info *info = &state->stack_info;
	unsigned long *mask = &state->stack_mask;
	bool reliable, reuse_sp;
	struct stack_frame *sf;
	unsigned long ip;

	memset(state, 0, sizeof(*state));
	state->task = task;
	state->regs = regs;

	/* Don't even attempt to start from user mode regs: */
	if (regs && user_mode(regs)) {
		info->type = STACK_TYPE_UNKNOWN;
		return;
	}

	/* Get current stack pointer and initialize stack info */
	if (get_stack_info(sp, task, info, mask) != 0 ||
	    !on_stack(info, sp, sizeof(struct stack_frame))) {
		/* Something is wrong with the stack pointer */
		info->type = STACK_TYPE_UNKNOWN;
		state->error = true;
		return;
	}

	/* Get the instruction pointer from pt_regs or the stack frame */
	if (regs) {
		ip = READ_ONCE_NOCHECK(regs->psw.addr);
		reliable = true;
		reuse_sp = true;
	} else {
		sf = (struct stack_frame *) sp;
		ip = READ_ONCE_NOCHECK(sf->gprs[8]);
		reliable = false;
		reuse_sp = false;
	}

#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	/* Decode any ftrace redirection */
	if (ip == (unsigned long) return_to_handler)
		ip = ftrace_graph_ret_addr(state->task, &state->graph_idx,
					   ip, NULL);
#endif

	/* Update unwind state */
	state->sp = sp;
	state->ip = ip;
	state->reliable = reliable;
	state->reuse_sp = reuse_sp;
}