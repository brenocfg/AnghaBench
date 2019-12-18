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
typedef  scalar_t__ vm_offset_t ;
struct stack {int dummy; } ;

/* Variables and functions */
 scalar_t__ CALLOFFSET ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  asttrapexit ; 
 int stack_put (struct stack*,scalar_t__) ; 
 int /*<<< orphan*/  stack_zero (struct stack*) ; 
 int /*<<< orphan*/  trapexit ; 

__attribute__((used)) static void
stack_capture(struct stack *st, vm_offset_t frame)
{
	vm_offset_t callpc;

	stack_zero(st);
	if (frame < PAGE_SIZE)
		return;
	while (1) {
		frame = *(vm_offset_t *)frame;
		if (frame < PAGE_SIZE)
			break;

	    #ifdef __powerpc64__
		callpc = *(vm_offset_t *)(frame + 16) - 4;
	    #else
		callpc = *(vm_offset_t *)(frame + 4) - 4;
	    #endif
		if ((callpc & 3) || (callpc < 0x100))
			break;

		/*
		 * Don't bother traversing trap-frames - there should
		 * be enough info down to the frame to work out where
		 * things are going wrong. Plus, prevents this shortened
		 * version of code from accessing user-space frames
		 */
		if (callpc + CALLOFFSET == (vm_offset_t) &trapexit ||
		    callpc + CALLOFFSET == (vm_offset_t) &asttrapexit)
			break;

		if (stack_put(st, callpc) == -1)
			break;
	}
}