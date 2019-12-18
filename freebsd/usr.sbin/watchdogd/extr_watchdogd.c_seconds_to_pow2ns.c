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
typedef  unsigned long long uint64_t ;

/* Variables and functions */
 scalar_t__ debugging ; 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 unsigned long long flsll (unsigned long long) ; 
 int /*<<< orphan*/  printf (char*,int,...) ; 

__attribute__((used)) static int
seconds_to_pow2ns(int seconds)
{
	uint64_t power;
	uint64_t ns;
	uint64_t shifted;

	if (seconds <= 0)
		errx(1, "seconds %d < 0", seconds);
	ns = ((uint64_t)seconds) * 1000000000ULL;
	power = flsll(ns);
	shifted = 1ULL << power;
	if (shifted <= ns) {
		power++;
	}
	if (debugging) {
		printf("shifted %lld\n", (long long)shifted);
		printf("seconds_to_pow2ns: seconds: %d, ns %lld, power %d\n",
		    seconds, (long long)ns, (int)power);
	}
	return (power);
}