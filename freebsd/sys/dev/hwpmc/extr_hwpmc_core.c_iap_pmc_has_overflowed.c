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
 int core_iap_width ; 
 unsigned long long rdpmc (int) ; 

__attribute__((used)) static int
iap_pmc_has_overflowed(int ri)
{
	uint64_t v;

	/*
	 * We treat a Core (i.e., Intel architecture v1) PMC as has
	 * having overflowed if its MSB is zero.
	 */
	v = rdpmc(ri);
	return ((v & (1ULL << (core_iap_width - 1))) == 0);
}