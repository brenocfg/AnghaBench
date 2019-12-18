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
struct of_phandle_args {scalar_t__* args; } ;
struct clk_hw {int dummy; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct clk* ERR_PTR (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 scalar_t__ TEGRA20_CLK_CDEV1 ; 
 scalar_t__ TEGRA20_CLK_CDEV2 ; 
 struct clk_hw* __clk_get_hw (struct clk*) ; 
 struct clk_hw* clk_hw_get_parent (struct clk_hw*) ; 
 struct clk* of_clk_src_onecell_get (struct of_phandle_args*,void*) ; 

__attribute__((used)) static struct clk *tegra20_clk_src_onecell_get(struct of_phandle_args *clkspec,
					       void *data)
{
	struct clk_hw *parent_hw;
	struct clk_hw *hw;
	struct clk *clk;

	clk = of_clk_src_onecell_get(clkspec, data);
	if (IS_ERR(clk))
		return clk;

	/*
	 * Tegra20 CDEV1 and CDEV2 clocks are a bit special case, their parent
	 * clock is created by the pinctrl driver. It is possible for clk user
	 * to request these clocks before pinctrl driver got probed and hence
	 * user will get an orphaned clock. That might be undesirable because
	 * user may expect parent clock to be enabled by the child.
	 */
	if (clkspec->args[0] == TEGRA20_CLK_CDEV1 ||
	    clkspec->args[0] == TEGRA20_CLK_CDEV2) {
		hw = __clk_get_hw(clk);

		parent_hw = clk_hw_get_parent(hw);
		if (!parent_hw)
			return ERR_PTR(-EPROBE_DEFER);
	}

	return clk;
}