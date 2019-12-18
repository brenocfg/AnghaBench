#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct freq_tbl {int /*<<< orphan*/  src; } ;
struct frac_entry {int den; scalar_t__ num; } ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_rcg2 {scalar_t__ cmd_rcgr; TYPE_1__ clkr; int /*<<< orphan*/  parent_map; int /*<<< orphan*/  hid_width; struct freq_tbl* freq_tbl; } ;
struct clk_rate_request {int best_parent_rate; int rate; int /*<<< orphan*/  best_parent_hw; } ;
struct clk_hw {int dummy; } ;
typedef  int s64 ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CFG_REG ; 
 int CFG_SRC_DIV_SHIFT ; 
 int EINVAL ; 
 int calc_rate (int,scalar_t__,int,int,int) ; 
 int /*<<< orphan*/  clk_hw_get_parent_by_index (struct clk_hw*,int) ; 
 int clk_hw_get_rate (int /*<<< orphan*/ ) ; 
 int div_s64 (int,scalar_t__) ; 
 struct frac_entry* frac_table_675m ; 
 struct frac_entry* frac_table_810m ; 
 int qcom_find_src_index (struct clk_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,scalar_t__,int*) ; 
 struct clk_rcg2* to_clk_rcg2 (struct clk_hw*) ; 

__attribute__((used)) static int clk_edp_pixel_determine_rate(struct clk_hw *hw,
					struct clk_rate_request *req)
{
	struct clk_rcg2 *rcg = to_clk_rcg2(hw);
	const struct freq_tbl *f = rcg->freq_tbl;
	const struct frac_entry *frac;
	int delta = 100000;
	s64 request;
	u32 mask = BIT(rcg->hid_width) - 1;
	u32 hid_div;
	int index = qcom_find_src_index(hw, rcg->parent_map, f->src);

	/* Force the correct parent */
	req->best_parent_hw = clk_hw_get_parent_by_index(hw, index);
	req->best_parent_rate = clk_hw_get_rate(req->best_parent_hw);

	if (req->best_parent_rate == 810000000)
		frac = frac_table_810m;
	else
		frac = frac_table_675m;

	for (; frac->num; frac++) {
		request = req->rate;
		request *= frac->den;
		request = div_s64(request, frac->num);
		if ((req->best_parent_rate < (request - delta)) ||
		    (req->best_parent_rate > (request + delta)))
			continue;

		regmap_read(rcg->clkr.regmap, rcg->cmd_rcgr + CFG_REG,
				&hid_div);
		hid_div >>= CFG_SRC_DIV_SHIFT;
		hid_div &= mask;

		req->rate = calc_rate(req->best_parent_rate,
				      frac->num, frac->den,
				      !!frac->den, hid_div);
		return 0;
	}

	return -EINVAL;
}