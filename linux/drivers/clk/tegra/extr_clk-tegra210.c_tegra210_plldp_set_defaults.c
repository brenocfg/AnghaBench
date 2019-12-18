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
 int /*<<< orphan*/  PLLDP_MISC0_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLDP_MISC1_CFG_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLDP_MISC2_CTRL1_DEFAULT_VALUE ; 
 int /*<<< orphan*/  PLLDP_MISC3_CTRL2_DEFAULT_VALUE ; 
 int /*<<< orphan*/  plldss_defaults (char*,struct tegra_clk_pll*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tegra210_plldp_set_defaults(struct tegra_clk_pll *plldp)
{
	plldss_defaults("PLL_DP", plldp, PLLDP_MISC0_DEFAULT_VALUE,
			PLLDP_MISC1_CFG_DEFAULT_VALUE,
			PLLDP_MISC2_CTRL1_DEFAULT_VALUE,
			PLLDP_MISC3_CTRL2_DEFAULT_VALUE);
}