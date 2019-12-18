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
struct meson_clk_mpll_data {int flags; int /*<<< orphan*/  misc; int /*<<< orphan*/  ssen; int /*<<< orphan*/  sdm_en; scalar_t__ init_count; int /*<<< orphan*/  init_regs; } ;
struct clk_regmap {int /*<<< orphan*/  map; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int CLK_MESON_MPLL_SPREAD_SPECTRUM ; 
 scalar_t__ MESON_PARM_APPLICABLE (int /*<<< orphan*/ *) ; 
 struct meson_clk_mpll_data* meson_clk_mpll_data (struct clk_regmap*) ; 
 int /*<<< orphan*/  meson_parm_write (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  regmap_multi_reg_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct clk_regmap* to_clk_regmap (struct clk_hw*) ; 

__attribute__((used)) static void mpll_init(struct clk_hw *hw)
{
	struct clk_regmap *clk = to_clk_regmap(hw);
	struct meson_clk_mpll_data *mpll = meson_clk_mpll_data(clk);

	if (mpll->init_count)
		regmap_multi_reg_write(clk->map, mpll->init_regs,
				       mpll->init_count);

	/* Enable the fractional part */
	meson_parm_write(clk->map, &mpll->sdm_en, 1);

	/* Set spread spectrum if possible */
	if (MESON_PARM_APPLICABLE(&mpll->ssen)) {
		unsigned int ss =
			mpll->flags & CLK_MESON_MPLL_SPREAD_SPECTRUM ? 1 : 0;
		meson_parm_write(clk->map, &mpll->ssen, ss);
	}

	/* Set the magic misc bit if required */
	if (MESON_PARM_APPLICABLE(&mpll->misc))
		meson_parm_write(clk->map, &mpll->misc, 1);
}