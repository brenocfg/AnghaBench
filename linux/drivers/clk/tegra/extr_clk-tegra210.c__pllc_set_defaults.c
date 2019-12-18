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
 int /*<<< orphan*/  tegra210_pllcx_set_defaults (char*,struct tegra_clk_pll*) ; 

__attribute__((used)) static void _pllc_set_defaults(struct tegra_clk_pll *pllcx)
{
	tegra210_pllcx_set_defaults("PLL_C", pllcx);
}