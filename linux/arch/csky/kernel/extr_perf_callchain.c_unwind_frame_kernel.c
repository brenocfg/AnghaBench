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
struct stackframe {int fp; int /*<<< orphan*/  lr; } ;

/* Variables and functions */
 int EPERM ; 
 int TASK_SIZE ; 
 scalar_t__ __kernel_text_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ftrace_graph_ret_addr (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ kstack_end (void*) ; 

__attribute__((used)) static int unwind_frame_kernel(struct stackframe *frame)
{
	if (kstack_end((void *)frame->fp))
		return -EPERM;
	if (frame->fp & 0x3 || frame->fp < TASK_SIZE)
		return -EPERM;

	*frame = *(struct stackframe *)frame->fp;
	if (__kernel_text_address(frame->lr)) {
		int graph = 0;

		frame->lr = ftrace_graph_ret_addr(NULL, &graph, frame->lr,
				NULL);
	}
	return 0;
}