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
struct trapframe {uintptr_t* fixreg; uintptr_t srr0; } ;

/* Variables and functions */
 scalar_t__ FRAME_OFFSET ; 
 scalar_t__ OFFSET ; 
 scalar_t__ RETURN_OFFSET ; 
 scalar_t__ RETURN_OFFSET64 ; 
 int /*<<< orphan*/  asttrapexit ; 
 int /*<<< orphan*/  trapexit ; 

__attribute__((used)) static __inline void
dtrace_next_sp_pc(uintptr_t sp, uintptr_t *nsp, uintptr_t *pc)
{
	vm_offset_t callpc;
	struct trapframe *frame;

#ifdef __powerpc64__
	callpc = *(vm_offset_t *)(sp + RETURN_OFFSET64);
#else
	callpc = *(vm_offset_t *)(sp + RETURN_OFFSET);
#endif

	/*
	 * trapexit() and asttrapexit() are sentinels
	 * for kernel stack tracing.
	 */
	if ((callpc + OFFSET == (vm_offset_t) &trapexit ||
	    callpc + OFFSET == (vm_offset_t) &asttrapexit)) {
		/* Access the trap frame */
		frame = (struct trapframe *)(sp + FRAME_OFFSET);

		if (nsp != NULL)
			*nsp = frame->fixreg[1];
		if (pc != NULL)
			*pc = frame->srr0;
		return;
	}

	if (nsp != NULL)
		*nsp = *(uintptr_t *)sp;
	if (pc != NULL)
		*pc = callpc;
}