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
typedef  size_t u32 ;
struct ingenic_clk {size_t idx; struct ingenic_cgu* cgu; } ;
struct TYPE_4__ {unsigned long div; } ;
struct TYPE_3__ {size_t shift; size_t* div_table; size_t div; scalar_t__ bits; scalar_t__ reg; } ;
struct ingenic_cgu_clk_info {int type; TYPE_2__ fixdiv; TYPE_1__ div; } ;
struct ingenic_cgu {scalar_t__ base; struct ingenic_cgu_clk_info* clock_info; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CGU_CLK_DIV ; 
 int CGU_CLK_FIXDIV ; 
 size_t GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 size_t readl (scalar_t__) ; 
 struct ingenic_clk* to_ingenic_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
ingenic_clk_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	struct ingenic_cgu *cgu = ingenic_clk->cgu;
	const struct ingenic_cgu_clk_info *clk_info;
	unsigned long rate = parent_rate;
	u32 div_reg, div;

	clk_info = &cgu->clock_info[ingenic_clk->idx];

	if (clk_info->type & CGU_CLK_DIV) {
		div_reg = readl(cgu->base + clk_info->div.reg);
		div = (div_reg >> clk_info->div.shift) &
		      GENMASK(clk_info->div.bits - 1, 0);

		if (clk_info->div.div_table)
			div = clk_info->div.div_table[div];
		else
			div = (div + 1) * clk_info->div.div;

		rate /= div;
	} else if (clk_info->type & CGU_CLK_FIXDIV) {
		rate /= clk_info->fixdiv.div;
	}

	return rate;
}