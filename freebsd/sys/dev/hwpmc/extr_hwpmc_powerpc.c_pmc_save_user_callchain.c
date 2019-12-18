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
typedef  uintptr_t uint32_t ;
struct trapframe {int srr1; } ;

/* Variables and functions */
 scalar_t__ PMC_TRAPFRAME_TO_FP (struct trapframe*) ; 
 uintptr_t PMC_TRAPFRAME_TO_PC (struct trapframe*) ; 
 int PSL_SF ; 
 uintptr_t fuword (uintptr_t*) ; 
 uintptr_t fuword32 (uintptr_t*) ; 

int
pmc_save_user_callchain(uintptr_t *cc, int maxsamples,
    struct trapframe *tf)
{
	uintptr_t *osp, *sp;
	int frames = 0;

	cc[frames++] = PMC_TRAPFRAME_TO_PC(tf);
	sp = (uintptr_t *)PMC_TRAPFRAME_TO_FP(tf);
	osp = NULL;

	for (; frames < maxsamples; frames++) {
		if (sp <= osp)
			break;
		osp = sp;
#ifdef __powerpc64__
		/* Check if 32-bit mode. */
		if (!(tf->srr1 & PSL_SF)) {
			cc[frames] = fuword32((uint32_t *)sp + 1);
			sp = (uintptr_t *)(uintptr_t)fuword32(sp);
		} else {
			cc[frames] = fuword(sp + 2);
			sp = (uintptr_t *)fuword(sp);
		}
#else
		cc[frames] = fuword32((uint32_t *)sp + 1);
		sp = (uintptr_t *)fuword32(sp);
#endif
	}

	return (frames);
}