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
 unsigned long long flsll (unsigned long long) ; 

__attribute__((used)) static int
seconds_to_pow2ns(int seconds)
{
	uint64_t power;
	uint64_t ns;
	uint64_t shifted;

	ns = ((uint64_t)seconds) * 1000000000ULL;
	power = flsll(ns);
	shifted = 1ULL << power;
	if (shifted <= ns) {
		power++;
	}
	return (power);
}