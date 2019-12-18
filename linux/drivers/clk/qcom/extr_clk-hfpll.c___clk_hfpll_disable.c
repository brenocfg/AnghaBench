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
struct regmap {int dummy; } ;
struct hfpll_data {int /*<<< orphan*/  mode_reg; } ;
struct TYPE_2__ {struct regmap* regmap; } ;
struct clk_hfpll {TYPE_1__ clkr; struct hfpll_data* d; } ;

/* Variables and functions */
 int PLL_BYPASSNL ; 
 int PLL_OUTCTRL ; 
 int PLL_RESET_N ; 
 int /*<<< orphan*/  regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __clk_hfpll_disable(struct clk_hfpll *h)
{
	struct hfpll_data const *hd = h->d;
	struct regmap *regmap = h->clkr.regmap;

	/*
	 * Disable the PLL output, disable test mode, enable the bypass mode,
	 * and assert the reset.
	 */
	regmap_update_bits(regmap, hd->mode_reg,
			   PLL_BYPASSNL | PLL_RESET_N | PLL_OUTCTRL, 0);
}