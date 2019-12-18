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
struct freq_tbl {int pre_div; unsigned long m; unsigned long n; int /*<<< orphan*/  src; int /*<<< orphan*/  member_0; } ;
struct frac_entry {int num; unsigned long den; } ;
struct TYPE_4__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg2 {scalar_t__ cmd_rcgr; TYPE_2__ clkr; TYPE_1__* parent_map; int /*<<< orphan*/  hid_width; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {int cfg; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_REG ; 
 int CFG_SRC_DIV_SHIFT ; 
 int CFG_SRC_SEL_MASK ; 
 int CFG_SRC_SEL_SHIFT ; 
 int EINVAL ; 
 int clk_hw_get_num_parents (struct clk_hw*) ; 
 int clk_rcg2_configure (struct clk_rcg2*,struct freq_tbl*) ; 
 struct frac_entry* frac_table_pixel ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_pixel_set_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long parent_rate)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	struct freq_tbl f = { 0 };
	const struct frac_entry *frac = frac_table_pixel;
	unsigned long request;
	int delta = 100000;
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 hid_div, cfg;
	int i, num_parents = clk_hw_get_num_parents(hw);

	regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG, &cfg);
	cfg &= CFG_SRC_SEL_MASK;
	cfg >>= CFG_SRC_SEL_SHIFT;

	for (i = 0; i < num_parents; i++)
		if (cfg == rcg->parent_map[i].cfg) {
			f.src = rcg->parent_map[i].src;
			break;
		}

	for (; frac->num; frac++) {
		request = (rate * frac->den) / frac->num;

		if ((parent_rate < (request - delta)) ||
			(parent_rate > (request + delta)))
			continue;

		regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
				&hid_div);
		f.pre_div = hid_div;
		f.pre_div >>= CFG_SRC_DIV_SHIFT;
		f.pre_div &= mask;
		f.m = frac->num;
		f.n = frac->den;

		return clk_rcg2_configure(rcg, &f);
	}
	return -EINVAL;
}