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
struct trapframe {int dummy; } ;

/* Variables and functions */
 uintptr_t OFFSET ; 
 scalar_t__ PAGE_SIZE ; 
 scalar_t__ PMC_TRAPFRAME_TO_FP (struct trapframe*) ; 
 uintptr_t PMC_TRAPFRAME_TO_PC (struct trapframe*) ; 
 int /*<<< orphan*/  asttrapexit ; 
 int /*<<< orphan*/  trapexit ; 

int
pmc_save_kernel_callchain(uintptr_t *cc, int maxsamples,
    struct trapframe *tf)
{
	uintptr_t *osp, *sp;
	uintptr_t pc;
	int frames = 0;

	cc[frames++] = PMC_TRAPFRAME_TO_PC(tf);
	sp = (uintptr_t *)PMC_TRAPFRAME_TO_FP(tf);
	osp = (uintptr_t *)PAGE_SIZE;

	for (; frames < maxsamples; frames++) {
		if (sp <= osp)
			break;
	    #ifdef __powerpc64__
		pc = sp[2];
	    #else
		pc = sp[1];
	    #endif
		if ((pc & 3) || (pc < 0x100))
			break;

		/*
		 * trapexit() and asttrapexit() are sentinels
		 * for kernel stack tracing.
		 * */
		if (pc + OFFSET == (uintptr_t) &trapexit ||
		    pc + OFFSET == (uintptr_t) &asttrapexit)
			break;

		cc[frames] = pc;
		osp = sp;
		sp = (uintptr_t *)*sp;
	}
	return (frames);
}