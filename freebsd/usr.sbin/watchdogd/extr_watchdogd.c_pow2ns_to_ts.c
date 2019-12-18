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
struct timespec {unsigned long long tv_sec; unsigned long long tv_nsec; } ;

/* Variables and functions */

__attribute__((used)) static void
pow2ns_to_ts(int pow2ns, struct timespec *ts)
{
	uint64_t ns;

	ns = 1ULL << pow2ns;
	ts->tv_sec = ns / 1000000000ULL;
	ts->tv_nsec = ns % 1000000000ULL;
}