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
struct clk_pllv3_vf610_mf {int mfn; int mfd; int mfi; } ;
struct clk_pllv3 {int div_mask; scalar_t__ base; scalar_t__ denom_offset; scalar_t__ num_offset; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long clk_pllv3_vf610_mf_to_rate (unsigned long,struct clk_pllv3_vf610_mf) ; 
 int readl_relaxed (scalar_t__) ; 
 struct clk_pllv3* to_clk_pllv3 (struct clk_hw*) ; 

__attribute__((used)) static unsigned long clk_pllv3_vf610_recalc_rate(struct clk_hw *hw,
					      unsigned long parent_rate)
{
	struct clk_pllv3 *pll = to_clk_pllv3(hw);
	struct clk_pllv3_vf610_mf mf;

	mf.mfn = readl_relaxed(pll->base + pll->num_offset);
	mf.mfd = readl_relaxed(pll->base + pll->denom_offset);
	mf.mfi = (readl_relaxed(pll->base) & pll->div_mask) ? 22 : 20;

	return clk_pllv3_vf610_mf_to_rate(parent_rate, mf);
}