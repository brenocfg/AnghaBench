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

__attribute__((used)) static int
x86_rdseed_store(u_long *buf)
{
	u_long rndval;
	int retry;

	retry = RETRY_COUNT;
	__asm __volatile(
	    "1:\n\t"
	    "rdseed	%1\n\t"	/* read randomness into rndval */
	    "jc		2f\n\t" /* CF is set on success, exit retry loop */
	    "dec	%0\n\t" /* otherwise, retry-- */
	    "jne	1b\n\t" /* and loop if retries are not exhausted */
	    "2:"
	    : "+r" (retry), "=r" (rndval) : : "cc");
	*buf = rndval;
	return (retry);
}