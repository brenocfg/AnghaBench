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

/* Variables and functions */

__attribute__((used)) static void axi_clkgen_calc_clk_params(unsigned int divider, unsigned int *low,
	unsigned int *high, unsigned int *edge, unsigned int *nocount)
{
	if (divider == 1)
		*nocount = 1;
	else
		*nocount = 0;

	*high = divider / 2;
	*edge = divider % 2;
	*low = divider - *high;
}