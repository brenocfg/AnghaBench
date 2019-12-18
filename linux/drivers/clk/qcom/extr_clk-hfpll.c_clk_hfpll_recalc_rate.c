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
typedef  unsigned long u32 ;
struct regmap {int dummy; } ;
struct hfpll_data {int /*<<< orphan*/  l_reg; } ;
struct clk_hw {int dummy; } ;
struct TYPE_2__ {struct regmap* regmap; } ;
struct clk_hfpll {TYPE_1__ clkr; struct hfpll_data* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned long*) ; 
 struct clk_hfpll* to_clk_hfpll (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_hfpll_recalc_rate(struct clk_hw *hw,
					   unsigned long parent_rate)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	u32 l_val;

	regmap_read(regmap, hd->l_reg, &l_val);

	return l_val * parent_rate;
}