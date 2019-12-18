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
struct clk_divider {int shift; int /*<<< orphan*/  width; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int clk_div_mask (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 struct clk_divider* to_clk_divider (struct clk_hw*) ; 

__attribute__((used)) static int clk_divider_is_enabled(struct clk_hw *hw)
{
	struct clk_divider *div = to_clk_divider(hw);
	u32 val;

	val = readl(div->reg) >> div->shift;
	val &= clk_div_mask(div->width);

	return val ? 1 : 0;
}