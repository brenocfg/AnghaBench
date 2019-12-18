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
struct tegra124_cpufreq_priv {int /*<<< orphan*/  cpu_clk; struct clk* dfll_clk; struct clk* pllp_clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 struct clk* clk_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (struct clk*) ; 
 int /*<<< orphan*/  clk_set_parent (int /*<<< orphan*/ ,struct clk*) ; 
 int clk_set_rate (struct clk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra124_cpu_switch_to_dfll(struct tegra124_cpufreq_priv *priv)
{
	struct clk *orig_parent;
	int ret;

	ret = clk_set_rate(priv->dfll_clk, clk_get_rate(priv->cpu_clk));
	if (ret)
		return ret;

	orig_parent = clk_get_parent(priv->cpu_clk);
	clk_set_parent(priv->cpu_clk, priv->pllp_clk);

	ret = clk_prepare_enable(priv->dfll_clk);
	if (ret)
		goto out;

	clk_set_parent(priv->cpu_clk, priv->dfll_clk);

	return 0;

out:
	clk_set_parent(priv->cpu_clk, orig_parent);

	return ret;
}