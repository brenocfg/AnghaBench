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
struct thread_info {unsigned long ksp; struct task_struct* task; } ;
struct task_struct {int dummy; } ;
struct stack_trace {scalar_t__ nr_entries; scalar_t__ max_entries; scalar_t__ skip; unsigned long* entries; } ;
struct sparc_stackf {unsigned long callers_pc; scalar_t__ fp; } ;
struct pt_regs {int tstate; unsigned long tpc; unsigned long* u_regs; } ;
struct ftrace_ret_stack {unsigned long ret; } ;

/* Variables and functions */
 unsigned long STACK_BIAS ; 
 int TSTATE_PRIV ; 
 size_t UREG_I6 ; 
 struct thread_info* current_thread_info () ; 
 struct ftrace_ret_stack* ftrace_graph_get_ret_stack (struct task_struct*,int) ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 scalar_t__ kstack_is_trap_frame (struct thread_info*,struct pt_regs*) ; 
 int /*<<< orphan*/  kstack_valid (struct thread_info*,unsigned long) ; 
 int /*<<< orphan*/  return_to_handler ; 
 int /*<<< orphan*/  stack_trace_flush () ; 

__attribute__((used)) static void __save_stack_trace(struct thread_info *tp,
			       struct stack_trace *trace,
			       bool skip_sched)
{
	unsigned long ksp, fp;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	struct task_struct *t;
	int graph = 0;
#endif

	if (tp == current_thread_info()) {
		stack_trace_flush();
		__asm__ __volatile__("mov %%fp, %0" : "=r" (ksp));
	} else {
		ksp = tp->ksp;
	}

	fp = ksp + STACK_BIAS;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
	t = tp->task;
#endif
	do {
		struct sparc_stackf *sf;
		struct pt_regs *regs;
		unsigned long pc;

		if (!kstack_valid(tp, fp))
			break;

		sf = (struct sparc_stackf *) fp;
		regs = (struct pt_regs *) (sf + 1);

		if (kstack_is_trap_frame(tp, regs)) {
			if (!(regs->tstate & TSTATE_PRIV))
				break;
			pc = regs->tpc;
			fp = regs->u_regs[UREG_I6] + STACK_BIAS;
		} else {
			pc = sf->callers_pc;
			fp = (unsigned long)sf->fp + STACK_BIAS;
		}

		if (trace->skip > 0)
			trace->skip--;
		else if (!skip_sched || !in_sched_functions(pc)) {
			trace->entries[trace->nr_entries++] = pc;
#ifdef CONFIG_FUNCTION_GRAPH_TRACER
			if ((pc + 8UL) == (unsigned long) &return_to_handler) {
				struct ftrace_ret_stack *ret_stack;
				ret_stack = ftrace_graph_get_ret_stack(t,
								       graph);
				if (ret_stack) {
					pc = ret_stack->ret;
					if (trace->nr_entries <
					    trace->max_entries)
						trace->entries[trace->nr_entries++] = pc;
					graph++;
				}
			}
#endif
		}
	} while (trace->nr_entries < trace->max_entries);
}