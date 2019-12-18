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
struct clk_factor_table {int div; unsigned int val; unsigned int mul; } ;

/* Variables and functions */

__attribute__((used)) static int _get_table_div_mul(const struct clk_factor_table *table,
			unsigned int val, unsigned int *mul, unsigned int *div)
{
	const struct clk_factor_table *clkt;

	for (clkt = table; clkt->div; clkt++) {
		if (clkt->val == val) {
			*mul = clkt->mul;
			*div = clkt->div;
			return 1;
		}
	}

	return 0;
}