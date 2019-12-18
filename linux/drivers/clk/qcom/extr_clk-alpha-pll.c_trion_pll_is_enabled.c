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
typedef  int u32 ;
struct regmap {int dummy; } ;
struct clk_alpha_pll {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  PLL_OPMODE (struct clk_alpha_pll*) ; 
 int PLL_OUTCTRL ; 
 int TRION_PLL_RUN ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int trion_pll_is_enabled(struct clk_alpha_pll *pll,
				struct regmap *regmap)
{
	u32 mode_regval, opmode_regval;
	int ret;

	ret = regmap_read(regmap, PLL_MODE(pll), &mode_regval);
	ret |= regmap_read(regmap, PLL_OPMODE(pll), &opmode_regval);
	if (ret)
		return 0;

	return ((opmode_regval & TRION_PLL_RUN) && (mode_regval & PLL_OUTCTRL));
}