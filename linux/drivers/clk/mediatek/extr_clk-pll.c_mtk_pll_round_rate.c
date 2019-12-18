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
typedef  int /*<<< orphan*/  u32 ;
struct mtk_clk_pll {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 long __mtk_pll_recalc_rate (struct mtk_clk_pll*,unsigned long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtk_pll_calc_values (struct mtk_clk_pll*,int /*<<< orphan*/ *,int*,unsigned long,unsigned long) ; 
 struct mtk_clk_pll* to_mtk_clk_pll (struct clk_hw*) ; 

__attribute__((used)) static long mtk_pll_round_rate(struct clk_hw *hw, unsigned long rate,
		unsigned long *prate)
{
	struct mtk_clk_pll *pll = to_mtk_clk_pll(hw);
	u32 pcw = 0;
	int postdiv;

	mtk_pll_calc_values(pll, &pcw, &postdiv, rate, *prate);

	return __mtk_pll_recalc_rate(pll, *prate, pcw, postdiv);
}