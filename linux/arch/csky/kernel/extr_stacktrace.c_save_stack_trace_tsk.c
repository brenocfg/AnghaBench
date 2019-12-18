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
struct task_struct {int dummy; } ;
struct stack_trace {int skip; unsigned long* entries; scalar_t__ nr_entries; scalar_t__ max_entries; } ;

/* Variables and functions */
 unsigned long THREAD_MASK ; 
 scalar_t__ THREAD_SIZE ; 
 int /*<<< orphan*/  __kernel_text_address (unsigned long) ; 
 struct task_struct* current ; 
 unsigned long ftrace_graph_ret_addr (struct task_struct*,int*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_sched_functions (unsigned long) ; 
 scalar_t__ thread_saved_fp (struct task_struct*) ; 

void save_stack_trace_tsk(struct task_struct *tsk, struct stack_trace *trace)
{
	unsigned long *fp, *stack_start, *stack_end;
	unsigned long addr;
	int skip = trace->skip;
	int savesched;
	int graph_idx = 0;

	if (tsk == current) {
		asm volatile("mov %0, r8\n":"=r"(fp));
		savesched = 1;
	} else {
		fp = (unsigned long *)thread_saved_fp(tsk);
		savesched = 0;
	}

	addr = (unsigned long) fp & THREAD_MASK;
	stack_start = (unsigned long *) addr;
	stack_end = (unsigned long *) (addr + THREAD_SIZE);

	while (fp > stack_start && fp < stack_end) {
		unsigned long lpp, fpp;

		fpp = fp[0];
		lpp = fp[1];
		if (!__kernel_text_address(lpp))
			break;
		else
			lpp = ftrace_graph_ret_addr(tsk, &graph_idx, lpp, NULL);

		if (savesched || !in_sched_functions(lpp)) {
			if (skip) {
				skip--;
			} else {
				trace->entries[trace->nr_entries++] = lpp;
				if (trace->nr_entries >= trace->max_entries)
					break;
			}
		}
		fp = (unsigned long *)fpp;
	}
}