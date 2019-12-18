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
struct hfpll_data {unsigned long user_vco_mask; unsigned long low_vco_max_rate; scalar_t__ l_reg; scalar_t__ user_reg; } ;
struct clk_hw {int /*<<< orphan*/  clk; } ;
struct TYPE_2__ {struct regmap* regmap; } ;
struct clk_hfpll {int /*<<< orphan*/  lock; TYPE_1__ clkr; struct hfpll_data* d; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clk_hfpll_disable (struct clk_hfpll*) ; 
 int /*<<< orphan*/  __clk_hfpll_enable (struct clk_hw*) ; 
 int __clk_is_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_read (struct regmap*,scalar_t__,unsigned long*) ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct clk_hfpll* to_clk_hfpll (struct clk_hw*) ; 

__attribute__((used)) static int clk_hfpll_set_rate(struct clk_hw *hw, unsigned long rate,
			      unsigned long parent_rate)
{
	struct clk_hfpll *h = to_clk_hfpll(hw);
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;
	unsigned long flags;
	u32 l_val, val;
	bool enabled;

	l_val = rate / parent_rate;

	spin_lock_irqsave(&h->lock, flags);

	enabled = __clk_is_enabled(hw->clk);
	if (enabled)
		__clk_hfpll_disable(h);

	/* Pick the right VCO. */
	if (hd->user_reg && hd->user_vco_mask) {
		regmap_read(regmap, hd->user_reg, &val);
		if (rate <= hd->low_vco_max_rate)
			val &= ~hd->user_vco_mask;
		else
			val |= hd->user_vco_mask;
		regmap_write(regmap, hd->user_reg, val);
	}

	regmap_write(regmap, hd->l_reg, l_val);

	if (enabled)
		__clk_hfpll_enable(hw);

	spin_unlock_irqrestore(&h->lock, flags);

	return 0;
}