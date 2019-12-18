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
struct pll_rate_tbl {unsigned long mode; unsigned long n; unsigned long m; } ;
struct clk_vco {scalar_t__ lock; int /*<<< orphan*/  cfg_reg; int /*<<< orphan*/  mode_reg; int /*<<< orphan*/  rtbl_cnt; struct pll_rate_tbl* rtbl; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned long PLL_DITH_FDBK_M_MASK ; 
 unsigned long PLL_DITH_FDBK_M_SHIFT ; 
 unsigned long PLL_DIV_N_MASK ; 
 unsigned long PLL_DIV_N_SHIFT ; 
 unsigned long PLL_MODE_MASK ; 
 unsigned long PLL_MODE_SHIFT ; 
 unsigned long PLL_NORM_FDBK_M_MASK ; 
 unsigned long PLL_NORM_FDBK_M_SHIFT ; 
 int /*<<< orphan*/  clk_round_rate_index (struct clk_hw*,unsigned long,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 unsigned long readl_relaxed (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_vco* to_clk_vco (struct clk_hw*) ; 
 int /*<<< orphan*/  vco_calc_rate ; 
 int /*<<< orphan*/  writel_relaxed (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clk_vco_set_rate(struct clk_hw *hw, unsigned long drate,
				unsigned long prate)
{
	struct clk_vco *vco = to_clk_vco(hw);
	struct pll_rate_tbl *rtbl = vco->rtbl;
	unsigned long flags = 0, val;
	int i;

	clk_round_rate_index(hw, drate, prate, vco_calc_rate, vco->rtbl_cnt,
			&i);

	if (vco->lock)
		spin_lock_irqsave(vco->lock, flags);

	val = readl_relaxed(vco->mode_reg);
	val &= ~(PLL_MODE_MASK << PLL_MODE_SHIFT);
	val |= (rtbl[i].mode & PLL_MODE_MASK) << PLL_MODE_SHIFT;
	writel_relaxed(val, vco->mode_reg);

	val = readl_relaxed(vco->cfg_reg);
	val &= ~(PLL_DIV_N_MASK << PLL_DIV_N_SHIFT);
	val |= (rtbl[i].n & PLL_DIV_N_MASK) << PLL_DIV_N_SHIFT;

	val &= ~(PLL_DITH_FDBK_M_MASK << PLL_DITH_FDBK_M_SHIFT);
	if (rtbl[i].mode)
		val |= (rtbl[i].m & PLL_DITH_FDBK_M_MASK) <<
			PLL_DITH_FDBK_M_SHIFT;
	else
		val |= (rtbl[i].m & PLL_NORM_FDBK_M_MASK) <<
			PLL_NORM_FDBK_M_SHIFT;

	writel_relaxed(val, vco->cfg_reg);

	if (vco->lock)
		spin_unlock_irqrestore(vco->lock, flags);

	return 0;
}