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
typedef  unsigned long long pmc_value_t ;

/* Variables and functions */
 int core_iap_width ; 

__attribute__((used)) static pmc_value_t
iap_perfctr_value_to_reload_count(pmc_value_t v)
{

	/* If the PMC has overflowed, return a reload count of zero. */
	if ((v & (1ULL << (core_iap_width - 1))) == 0)
		return (0);
	v &= (1ULL << core_iap_width) - 1;
	return (1ULL << core_iap_width) - v;
}