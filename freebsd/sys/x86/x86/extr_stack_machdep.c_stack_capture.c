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
typedef  TYPE_1__* x86_frame_t ;
typedef  scalar_t__ vm_offset_t ;
struct thread {scalar_t__ td_kstack; int td_kstack_pages; } ;
struct stack {int dummy; } ;
typedef  scalar_t__ register_t ;
struct TYPE_2__ {scalar_t__ f_retaddr; struct TYPE_2__* f_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  INKERNEL (scalar_t__) ; 
 int PAGE_SIZE ; 
 int stack_put (struct stack*,scalar_t__) ; 
 int /*<<< orphan*/  stack_zero (struct stack*) ; 

__attribute__((used)) static void
stack_capture(struct thread *td, struct stack *st, register_t fp)
{
	x86_frame_t frame;
	vm_offset_t callpc;

	stack_zero(st);
	frame = (x86_frame_t)fp;
	while (1) {
		if ((vm_offset_t)frame < td->td_kstack ||
		    (vm_offset_t)frame >= td->td_kstack +
		    td->td_kstack_pages * PAGE_SIZE)
			break;
		callpc = frame->f_retaddr;
		if (!INKERNEL(callpc))
			break;
		if (stack_put(st, callpc) == -1)
			break;
		if (frame->f_frame <= frame)
			break;
		frame = frame->f_frame;
	}
}