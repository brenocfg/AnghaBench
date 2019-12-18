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
struct reg {scalar_t__ ctr; int cr; } ;

/* Variables and functions */

__attribute__((used)) static int
fasttrap_branch_taken(int bo, int bi, struct reg *regs)
{
	int crzero = 0;

	/* Branch always? */
	if ((bo & 0x14) == 0x14)
		return 1;

	/* Handle decrementing ctr */
	if (!(bo & 0x04)) {
		--regs->ctr;
		crzero = (regs->ctr == 0);
		if (bo & 0x10) {
			return (!(crzero ^ (bo >> 1)));
		}
	}

	return (crzero | (((regs->cr >> (31 - bi)) ^ (bo >> 3)) ^ 1));
}