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
typedef  unsigned int u64 ;
typedef  unsigned int u32 ;
struct ingenic_clk {size_t idx; struct ingenic_cgu* cgu; } ;
struct ingenic_cgu_pll_info {unsigned int m_shift; unsigned int n_shift; unsigned int od_shift; unsigned int od_max; unsigned int* od_encoding; int /*<<< orphan*/  bypass_bit; int /*<<< orphan*/  no_bypass_bit; scalar_t__ od_bits; scalar_t__ n_offset; scalar_t__ n_bits; scalar_t__ m_offset; scalar_t__ m_bits; scalar_t__ reg; } ;
struct ingenic_cgu_clk_info {scalar_t__ type; struct ingenic_cgu_pll_info pll; } ;
struct ingenic_cgu {int /*<<< orphan*/  lock; scalar_t__ base; struct ingenic_cgu_clk_info* clock_info; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ CGU_CLK_PLL ; 
 unsigned int GENMASK (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned long div_u64 (unsigned int,unsigned int) ; 
 unsigned int readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct ingenic_clk* to_ingenic_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long
ingenic_pll_recalc_rate(struct clk_hw *hw, unsigned long parent_rate)
{
	struct ingenic_clk *ingenic_clk = to_ingenic_clk(hw);
	struct ingenic_cgu *cgu = ingenic_clk->cgu;
	const struct ingenic_cgu_clk_info *clk_info;
	const struct ingenic_cgu_pll_info *pll_info;
	unsigned m, n, od_enc, od;
	bool bypass;
	unsigned long flags;
	u32 ctl;

	clk_info = &cgu->clock_info[ingenic_clk->idx];
	BUG_ON(clk_info->type != CGU_CLK_PLL);
	pll_info = &clk_info->pll;

	spin_lock_irqsave(&cgu->lock, flags);
	ctl = readl(cgu->base + pll_info->reg);
	spin_unlock_irqrestore(&cgu->lock, flags);

	m = (ctl >> pll_info->m_shift) & GENMASK(pll_info->m_bits - 1, 0);
	m += pll_info->m_offset;
	n = (ctl >> pll_info->n_shift) & GENMASK(pll_info->n_bits - 1, 0);
	n += pll_info->n_offset;
	od_enc = ctl >> pll_info->od_shift;
	od_enc &= GENMASK(pll_info->od_bits - 1, 0);
	bypass = !pll_info->no_bypass_bit &&
		 !!(ctl & BIT(pll_info->bypass_bit));

	if (bypass)
		return parent_rate;

	for (od = 0; od < pll_info->od_max; od++) {
		if (pll_info->od_encoding[od] == od_enc)
			break;
	}
	BUG_ON(od == pll_info->od_max);
	od++;

	return div_u64((u64)parent_rate * m, n * od);
}