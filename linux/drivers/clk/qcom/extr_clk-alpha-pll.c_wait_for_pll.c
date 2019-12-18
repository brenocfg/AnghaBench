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
struct TYPE_2__ {int /*<<< orphan*/  regmap; int /*<<< orphan*/  hw; } ;
struct clk_alpha_pll {TYPE_1__ clkr; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  PLL_MODE (struct clk_alpha_pll*) ; 
 int /*<<< orphan*/  WARN (int,char*,char const*,char const*) ; 
 char* clk_hw_get_name (int /*<<< orphan*/ *) ; 
 int regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int wait_for_pll(struct clk_alpha_pll *pll, u32 mask, bool inverse,
			const char *action)
{
	u32 val;
	int count;
	int ret;
	const char *name = clk_hw_get_name(&pll->clkr.hw);

	ret = regmap_read(pll->clkr.regmap, PLL_MODE(pll), &val);
	if (ret)
		return ret;

	for (count = 100; count > 0; count--) {
		ret = regmap_read(pll->clkr.regmap, PLL_MODE(pll), &val);
		if (ret)
			return ret;
		if (inverse && !(val & mask))
			return 0;
		else if ((val & mask) == mask)
			return 0;

		udelay(1);
	}

	WARN(1, "%s failed to %s!\n", name, action);
	return -ETIMEDOUT;
}