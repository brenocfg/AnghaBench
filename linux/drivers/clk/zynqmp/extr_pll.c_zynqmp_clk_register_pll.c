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
typedef  int /*<<< orphan*/  u32 ;
struct clk_hw {struct clk_init_data* init; } ;
struct zynqmp_pll {struct clk_hw hw; int /*<<< orphan*/  clk_id; } ;
struct clock_topology {int /*<<< orphan*/  flag; } ;
struct clk_init_data {char const* name; char const* const* parent_names; int num_parents; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct clk_hw* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PS_PLL_VCO_MAX ; 
 int /*<<< orphan*/  PS_PLL_VCO_MIN ; 
 int clk_hw_register (int /*<<< orphan*/ *,struct clk_hw*) ; 
 int /*<<< orphan*/  clk_hw_set_rate_range (struct clk_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct zynqmp_pll*) ; 
 struct zynqmp_pll* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*,int) ; 
 int /*<<< orphan*/  zynqmp_pll_ops ; 

struct clk_hw *zynqmp_clk_register_pll(const char *name, u32 clk_id,
				       const char * const *parents,
				       u8 num_parents,
				       const struct clock_topology *nodes)
{
	struct zynqmp_pll *pll;
	struct clk_hw *hw;
	struct clk_init_data init;
	int ret;

	init.name = name;
	init.ops = &zynqmp_pll_ops;
	init.flags = nodes->flag;
	init.parent_names = parents;
	init.num_parents = 1;

	pll = kzalloc(sizeof(*pll), GFP_KERNEL);
	if (!pll)
		return ERR_PTR(-ENOMEM);

	pll->hw.init = &init;
	pll->clk_id = clk_id;

	hw = &pll->hw;
	ret = clk_hw_register(NULL, hw);
	if (ret) {
		kfree(pll);
		return ERR_PTR(ret);
	}

	clk_hw_set_rate_range(hw, PS_PLL_VCO_MIN, PS_PLL_VCO_MAX);
	if (ret < 0)
		pr_err("%s:ERROR clk_set_rate_range failed %d\n", name, ret);

	return hw;
}