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
struct freq_tbl {int pre_div; int m; int n; int /*<<< orphan*/  freq; int /*<<< orphan*/  src; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  hw; } ;
struct clk_rcg2 {scalar_t__ cmd_rcgr; TYPE_2__ clkr; int /*<<< orphan*/  mnd_width; TYPE_1__* parent_map; int /*<<< orphan*/  hid_width; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {int cfg; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int CFG_MODE_MASK ; 
 int CFG_MODE_SHIFT ; 
 int CFG_SRC_SEL_MASK ; 
 int CFG_SRC_SEL_SHIFT ; 
 scalar_t__ SE_PERF_DFSR (unsigned int) ; 
 scalar_t__ SE_PERF_M_DFSR (unsigned int) ; 
 scalar_t__ SE_PERF_N_DFSR (unsigned int) ; 
 int /*<<< orphan*/  calc_rate (unsigned long,int,int,int,int) ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 struct clk_hw* clk_hw_get_parent_by_index (int /*<<< orphan*/ *,int) ; 
 unsigned long clk_hw_get_rate (struct clk_hw*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static void clk_rcg2_dfs_populate_freq(struct clk_hw *hw, unsigned int l,
				       struct freq_tbl *f)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	struct clk_hw *p;
	unsigned long prate = 0;
	u32 val, mask, cfg, mode;
	int i, num_parents;

	regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + SE_PERF_DFSR(l), &cfg);

	mask = BIT(rcg->hid_width) - 1;
	f->pre_div = 1;
	if (cfg & mask)
		f->pre_div = cfg & mask;

	cfg &= CFG_SRC_SEL_MASK;
	cfg >>= CFG_SRC_SEL_SHIFT;

	num_parents = clk_hw_get_num_parents(hw);
	for (i = 0; i < num_parents; i++) {
		if (cfg == rcg->parent_map[i].cfg) {
			f->src = rcg->parent_map[i].src;
			p = clk_hw_get_parent_by_index(&rcg->clkr.hw, i);
			prate = clk_hw_get_rate(p);
		}
	}

	mode = cfg & CFG_MODE_MASK;
	mode >>= CFG_MODE_SHIFT;
	if (mode) {
		mask = BIT(rcg->mnd_width) - 1;
		regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + SE_PERF_M_DFSR(l),
			    &val);
		val &= mask;
		f->m = val;

		regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + SE_PERF_N_DFSR(l),
			    &val);
		val = ~val;
		val &= mask;
		val += f->m;
		f->n = val;
	}

	f->freq = calc_rate(prate, f->m, f->n, mode, f->pre_div);
}