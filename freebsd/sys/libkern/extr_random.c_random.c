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
typedef  long u_long ;

/* Variables and functions */
 long randseed ; 

u_long
random()
{
	long x, hi, lo, t;

	/*
	 * Compute x[n + 1] = (7^5 * x[n]) mod (2^31 - 1).
	 * From "Random number generators: good ones are hard to find",
	 * Park and Miller, Communications of the ACM, vol. 31, no. 10,
	 * October 1988, p. 1195.
	 */
	/* Can't be initialized with 0, so use another value. */
	if ((x = randseed) == 0)
		x = 123459876;
	hi = x / 127773;
	lo = x % 127773;
	t = 16807 * lo - 2836 * hi;
	if (t < 0)
		t += 0x7fffffff;
	randseed = t;
	return (t);
}