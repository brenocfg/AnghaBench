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
struct ingenic_clk {int dummy; } ;
struct ingenic_cgu_clk_info {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long ingenic_pll_calc (struct ingenic_cgu_clk_info const*,unsigned long,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct ingenic_cgu_clk_info* to_clk_info (struct ingenic_clk*) ; 
 struct ingenic_clk* to_ingenic_clk (struct clk_hw*) ; 

__attribute__((used)) static long
ingenic_pll_round_rate(struct clk_hw *hw, unsigned long req_rate,
		       unsigned long *prate)
{
	struct ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	const struct ingenic_cgu_clk_info *clk_info = to_clk_info(ingenic_clk);

	return ingenic_pll_calc(clk_info, req_rate, *prate, NULL, NULL, NULL);
}