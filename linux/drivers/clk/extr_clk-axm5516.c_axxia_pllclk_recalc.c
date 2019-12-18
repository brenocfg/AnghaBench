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
struct clk_hw {int dummy; } ;
struct axxia_pllclk {int /*<<< orphan*/  reg; } ;
struct axxia_clk {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct axxia_clk* to_axxia_clk (struct clk_hw*) ; 
 struct axxia_pllclk* to_axxia_pllclk (struct axxia_clk*) ; 

__attribute__((used)) static unsigned long
axxia_pllclk_recalc(struct clk_hw *hw, unsigned long parent_rate)
{
	struct axxia_clk *aclk = to_axxia_clk(hw);
	struct axxia_pllclk *pll = to_axxia_pllclk(aclk);
	unsigned long rate, fbdiv, refdiv, postdiv;
	u32 control;

	regmap_read(aclk->regmap, pll->reg, &control);
	postdiv = ((control >> 0) & 0xf) + 1;
	fbdiv   = ((control >> 4) & 0xfff) + 3;
	refdiv  = ((control >> 16) & 0x1f) + 1;
	rate = (parent_rate / (refdiv * postdiv)) * fbdiv;

	return rate;
}