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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  regmap; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_UPDATE ; 
 int PLL_UPDATE_BYPASS ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int wait_for_pll_update (struct clk_alpha_pll*) ; 
 int wait_for_pll_update_ack_clear (struct clk_alpha_pll*) ; 
 int wait_for_pll_update_ack_set (struct clk_alpha_pll*) ; 

__attribute__((used)) static int __clk_alpha_pll_update_latch(struct clk_alpha_pll *pll)
{
	int ret;
	u32 mode;

	regmap_read(pll->clkr.regmap, PLL_MODE(pll), &mode);

	/* Latch the input to the PLL */
	regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), PLL_UPDATE,
			   PLL_UPDATE);

	/* Wait for 2 reference cycle before checking ACK bit */
	udelay(1);

	/*
	 * PLL will latch the new L, Alpha and freq control word.
	 * PLL will respond by raising PLL_ACK_LATCH output when new programming
	 * has been latched in and PLL is being updated. When
	 * UPDATE_LOGIC_BYPASS bit is not set, PLL_UPDATE will be cleared
	 * automatically by hardware when PLL_ACK_LATCH is asserted by PLL.
	 */
	if (mode & PLL_UPDATE_BYPASS) {
		ret = wait_for_pll_update_ack_set(pll);
		if (ret)
			return ret;

		regmap_update_bits(pll->clkr.regmap, PLL_MODE(pll), PLL_UPDATE, 0);
	} else {
		ret = wait_for_pll_update(pll);
		if (ret)
			return ret;
	}

	ret = wait_for_pll_update_ack_clear(pll);
	if (ret)
		return ret;

	/* Wait for PLL output to stabilize */
	udelay(10);

	return 0;
}