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
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_unregister (struct clk*) ; 

void imx_unregister_clocks(struct clk *clks[], unsigned int count)
{
	unsigned int i;

	for (i = 0; i < count; i++)
		clk_unregister(clks[i]);
}