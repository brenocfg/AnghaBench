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
typedef  int /*<<< orphan*/  u_long ;

/* Variables and functions */
 int RETRY_COUNT ; 

__attribute__((used)) static inline int
darn_rng_store(u_long *buf)
{
	u_long rndval;
	int retry;

	for (retry = RETRY_COUNT; retry > 0; --retry) {
		/* "DARN %rN, 1" instruction */
		/*
		 * Arguments for DARN: rN and "L", where "L" can be one of:
		 * 0 - 32-bit conditional random number
		 * 1 - Conditional random number (conditioned to remove bias)
		 * 2 - Raw random number	 (unprocessed, may include bias)
		 * 3 - Reserved
		 */
	    	__asm __volatile(".long 0x7c0105e6 | (%0 << 21)" :
	    	    "+r"(rndval));
		if (rndval != ~0)
			break;
	}

	*buf = rndval;
	return (retry);
}