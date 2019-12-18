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
typedef  int vm_offset_t ;
struct trapframe {int srr1; } ;

/* Variables and functions */
 scalar_t__ FRAME_OFFSET ; 
 int /*<<< orphan*/  INKERNEL (uintptr_t) ; 
 int OFFSET ; 
 int PSL_PR ; 
 scalar_t__ RETURN_OFFSET ; 
 scalar_t__ RETURN_OFFSET64 ; 
 int /*<<< orphan*/  asttrapexit ; 
 int /*<<< orphan*/  trapexit ; 

__attribute__((used)) static __inline int
dtrace_sp_inkernel(uintptr_t sp)
{
	struct trapframe *frame;
	vm_offset_t callpc;

	/* Not within the kernel, or not aligned. */
	if (!INKERNEL(sp) || (sp & 0xf) != 0)
		return (0);
#ifdef __powerpc64__
	callpc = *(vm_offset_t *)(sp + RETURN_OFFSET64);
#else
	callpc = *(vm_offset_t *)(sp + RETURN_OFFSET);
#endif
	if ((callpc & 3) || (callpc < 0x100))
		return (0);

	/*
	 * trapexit() and asttrapexit() are sentinels
	 * for kernel stack tracing.
	 */
	if (callpc + OFFSET == (vm_offset_t) &trapexit ||
	    callpc + OFFSET == (vm_offset_t) &asttrapexit) {
		frame = (struct trapframe *)(sp + FRAME_OFFSET);

		return ((frame->srr1 & PSL_PR) == 0);
	}

	return (1);
}