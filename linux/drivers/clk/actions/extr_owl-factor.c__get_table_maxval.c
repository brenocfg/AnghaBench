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
struct clk_factor_table {unsigned int val; scalar_t__ div; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int _get_table_maxval(const struct clk_factor_table *table)
{
	unsigned int maxval = 0;
	const struct clk_factor_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->val > maxval)
			maxval = clkt->val;
	return maxval;
}