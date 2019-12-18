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
struct tegra_clk_pll {int dummy; } ;

/* Variables and functions */
 int clk_pll_wait_for_lock (struct tegra_clk_pll*) ; 

int tegra_pll_wait_for_lock(struct tegra_clk_pll *pll)
{
	return clk_pll_wait_for_lock(pll);
}