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
struct meson_clk_mpll_data {scalar_t__ lock; int /*<<< orphan*/  n2; int /*<<< orphan*/  sdm; int /*<<< orphan*/  flags; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __acquire (scalar_t__) ; 
 int /*<<< orphan*/  __release (scalar_t__) ; 
 struct meson_clk_mpll_data* meson_clk_mpll_data (struct clk_regmap*) ; 
 int /*<<< orphan*/  meson_parm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  params_from_rate (unsigned long,unsigned long,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (scalar_t__,unsigned long) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static int mpll_set_rate(struct clk_hw *hw,
			 unsigned long rate,
			 unsigned long parent_rate)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);
	unsigned int sdm, n2;
	unsigned long flags = 0;

	params_from_rate(rate, parent_rate, &sdm, &n2, mpll->flags);

	if (mpll->lock)
		spin_lock_irqsave(mpll->lock, flags);
	else
		__acquire(mpll->lock);

	/* Set the fractional part */
	meson_parm_write(clk->map, &mpll->sdm, sdm);

	/* Set the integer divider part */
	meson_parm_write(clk->map, &mpll->n2, n2);

	if (mpll->lock)
		spin_unlock_irqrestore(mpll->lock, flags);
	else
		__release(mpll->lock);

	return 0;
}