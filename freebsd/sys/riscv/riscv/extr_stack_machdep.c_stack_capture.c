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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct unwind_state {scalar_t__ pc; scalar_t__ fp; } ;
struct stack {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INKERNEL (int /*<<< orphan*/ ) ; 
 int stack_put (struct stack*,scalar_t__) ; 
 int /*<<< orphan*/  stack_zero (struct stack*) ; 
 int /*<<< orphan*/  unwind_frame (struct unwind_state*) ; 

__attribute__((used)) static void
stack_capture(struct stack *st, struct unwind_state *frame)
{

	stack_zero(st);

	while (1) {
		unwind_frame(frame);
		if (!INKERNEL((vm_offset_t)frame->fp) ||
		     !INKERNEL((vm_offset_t)frame->pc))
			break;
		if (stack_put(st, frame->pc) == -1)
			break;
	}
}