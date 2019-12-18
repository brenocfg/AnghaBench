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
typedef  int u8 ;
typedef  int u32 ;
struct clk_hw {int dummy; } ;
struct clk_dmn {int /*<<< orphan*/  regofs; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 char* clk_hw_get_name (struct clk_hw*) ; 
 int clkc_readl (int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 struct clk_dmn* to_dmnclk (struct clk_hw*) ; 

__attribute__((used)) static u8 dmn_clk_get_parent(struct clk_hw *hw)
{
	struct clk_dmn *clk = to_dmnclk(hw);
	u32 cfg = clkc_readl(clk->regofs);
	const char *name = clk_hw_get_name(hw);

	/* parent of io domain can only be pll3 */
	if (strcmp(name, "io") == 0)
		return 4;

	WARN_ON((cfg & (BIT(3) - 1)) > 4);

	return cfg & (BIT(3) - 1);
}