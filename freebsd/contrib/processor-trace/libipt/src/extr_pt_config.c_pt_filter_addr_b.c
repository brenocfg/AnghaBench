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
typedef  int uint8_t ;
typedef  unsigned long long uint64_t ;
struct pt_conf_addr_filter {unsigned long long addr0_a; } ;

/* Variables and functions */
 int pt_filter_addr_ncfg () ; 

uint64_t pt_filter_addr_b(const struct pt_conf_addr_filter *filter, uint8_t n)
{
	const uint64_t *addr;

	if (!filter)
		return 0ull;

	if (pt_filter_addr_ncfg() <= n)
		return 0ull;

	addr = &filter->addr0_a;
	return addr[(2 * n) + 1];
}