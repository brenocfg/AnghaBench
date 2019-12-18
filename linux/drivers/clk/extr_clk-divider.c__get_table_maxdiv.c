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
typedef  int /*<<< orphan*/  u8 ;
struct clk_div_table {int div; unsigned int val; } ;

/* Variables and functions */
 unsigned int clk_div_mask (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int _get_table_maxdiv(const struct clk_div_table *table,
				      u8 width)
{
	unsigned int maxdiv = 0, mask = clk_div_mask(width);
	const struct clk_div_table *clkt;

	for (clkt = table; clkt->div; clkt++)
		if (clkt->div > maxdiv && clkt->val <= mask)
			maxdiv = clkt->div;
	return maxdiv;
}