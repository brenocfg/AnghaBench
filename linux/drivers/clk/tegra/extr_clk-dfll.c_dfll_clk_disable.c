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
struct tegra_dfll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 struct tegra_dfll* clk_hw_to_dfll (struct clk_hw*) ; 
 int /*<<< orphan*/  dfll_disable (struct tegra_dfll*) ; 
 int dfll_unlock (struct tegra_dfll*) ; 

__attribute__((used)) static void dfll_clk_disable(struct clk_hw *hw)
{
	struct tegra_dfll *td = clk_hw_to_dfll(hw);
	int ret;

	ret = dfll_unlock(td);
	if (!ret)
		dfll_disable(td);
}