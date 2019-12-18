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
struct stackframe {unsigned long fp; unsigned long lp; unsigned long* sp; } ;

/* Variables and functions */
 int EPERM ; 
 size_t FP_OFFSET ; 
 unsigned long TASK_SIZE ; 
 scalar_t__ __kernel_text_address (unsigned long) ; 
 void* ftrace_graph_ret_addr (int /*<<< orphan*/ *,int*,unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kstack_end (void*) ; 
 int /*<<< orphan*/ * tsk ; 

__attribute__((used)) static int unwind_frame_kernel(struct stackframe *frame)
{
	int graph = 0;
#ifdef CONFIG_FRAME_POINTER
	/* 0x3 means misalignment */
	if (!kstack_end((void *)frame->fp) &&
	    !((unsigned long)frame->fp & 0x3) &&
	    ((unsigned long)frame->fp >= TASK_SIZE)) {
		/*
		 *	The array index is based on the ABI, the below graph
		 *	illustrate the reasons.
		 *	Function call procedure: "smw" and "lmw" will always
		 *	update SP and FP for you automatically.
		 *
		 *	Stack                                 Relative Address
		 *	|  |                                          0
		 *	----
		 *	|LP| <-- SP(before smw)  <-- FP(after smw)   -1
		 *	----
		 *	|FP|                                         -2
		 *	----
		 *	|  | <-- SP(after smw)                       -3
		 */
		frame->lp = ((unsigned long *)frame->fp)[-1];
		frame->fp = ((unsigned long *)frame->fp)[FP_OFFSET];
		/* make sure CONFIG_FUNCTION_GRAPH_TRACER is turned on */
		if (__kernel_text_address(frame->lp))
			frame->lp = ftrace_graph_ret_addr
						(NULL, &graph, frame->lp, NULL);

		return 0;
	} else {
		return -EPERM;
	}
#else
	/*
	 * You can refer to arch/nds32/kernel/traps.c:__dump()
	 * Treat "sp" as "fp", but the "sp" is one frame ahead of "fp".
	 * And, the "sp" is not always correct.
	 *
	 *   Stack                                 Relative Address
	 *   |  |                                          0
	 *   ----
	 *   |LP| <-- SP(before smw)                      -1
	 *   ----
	 *   |  | <-- SP(after smw)                       -2
	 *   ----
	 */
	if (!kstack_end((void *)frame->sp)) {
		frame->lp = ((unsigned long *)frame->sp)[1];
		/* TODO: How to deal with the value in first
		 * "sp" is not correct?
		 */
		if (__kernel_text_address(frame->lp))
			frame->lp = ftrace_graph_ret_addr
						(tsk, &graph, frame->lp, NULL);

		frame->sp = ((unsigned long *)frame->sp) + 1;

		return 0;
	} else {
		return -EPERM;
	}
#endif
}