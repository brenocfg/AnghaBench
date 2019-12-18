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
struct trapframe {uintptr_t pc; uintptr_t sp; uintptr_t ra; } ;
typedef  uintptr_t register_t ;

/* Variables and functions */
 scalar_t__ pmc_next_frame (uintptr_t*,uintptr_t*) ; 

int
pmc_save_kernel_callchain(uintptr_t *cc, int nframes,
    struct trapframe *tf)
{
	register_t pc, ra, sp;
	int frames = 0;

	pc = tf->pc;
	sp = tf->sp;
	ra = tf->ra;

	cc[frames++] = pc;

#ifdef	HWPMC_MIPS_BACKTRACE
	/*
	 * Unwind, and unwind, and unwind
	 */
	while (1) {
		if (frames >= nframes)
			break;

		if (pmc_next_frame(&pc, &sp) < 0)
			break;

		cc[frames++] = pc;
	}
#endif

	return (frames);
}