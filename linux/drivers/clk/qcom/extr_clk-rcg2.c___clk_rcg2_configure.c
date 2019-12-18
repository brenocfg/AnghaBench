#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct freq_tbl {int n; int m; int pre_div; int /*<<< orphan*/  src; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  regmap; struct clk_hw hw; } ;
struct clk_rcg2 {TYPE_1__ clkr; scalar_t__ mnd_width; TYPE_2__* parent_map; scalar_t__ hid_width; } ;
struct TYPE_4__ {int cfg; } ;

/* Variables and functions */
 int BIT (scalar_t__) ; 
 int CFG_HW_CLK_CTRL_MASK ; 
 int CFG_MODE_DUAL_EDGE ; 
 int CFG_MODE_MASK ; 
 int CFG_SRC_DIV_SHIFT ; 
 int CFG_SRC_SEL_MASK ; 
 int CFG_SRC_SEL_SHIFT ; 
 int /*<<< orphan*/  RCG_CFG_OFFSET (struct clk_rcg2*) ; 
 int /*<<< orphan*/  RCG_D_OFFSET (struct clk_rcg2*) ; 
 int /*<<< orphan*/  RCG_M_OFFSET (struct clk_rcg2*) ; 
 int /*<<< orphan*/  RCG_N_OFFSET (struct clk_rcg2*) ; 
 int qcom_find_src_index (struct clk_hw*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int __clk_rcg2_configure(struct clk_rcg2 *rcg, const struct freq_tbl *f)
{
	u32 cfg, mask;
	struct clk_hw *hw = &rcg->clkr.hw;
	int ret, index = qcom_find_src_index(hw, rcg->parent_map, f->src);

	if (index < 0)
		return index;

	if (rcg->mnd_width && f->n) {
		mask = BIT(rcg->mnd_width) - 1;
		ret = regmap_update_bits(rcg->clkr.regmap,
				RCG_M_OFFSET(rcg), mask, f->m);
		if (ret)
			return ret;

		ret = regmap_update_bits(rcg->clkr.regmap,
				RCG_N_OFFSET(rcg), mask, ~(f->n - f->m));
		if (ret)
			return ret;

		ret = regmap_update_bits(rcg->clkr.regmap,
				RCG_D_OFFSET(rcg), mask, ~f->n);
		if (ret)
			return ret;
	}

	mask = BIT(rcg->hid_width) - 1;
	mask |= CFG_SRC_SEL_MASK | CFG_MODE_MASK | CFG_HW_CLK_CTRL_MASK;
	cfg = f->pre_div << CFG_SRC_DIV_SHIFT;
	cfg |= rcg->parent_map[index].cfg << CFG_SRC_SEL_SHIFT;
	if (rcg->mnd_width && f->n && (f->m != f->n))
		cfg |= CFG_MODE_DUAL_EDGE;
	return regmap_update_bits(rcg->clkr.regmap, RCG_CFG_OFFSET(rcg),
					mask, cfg);
}