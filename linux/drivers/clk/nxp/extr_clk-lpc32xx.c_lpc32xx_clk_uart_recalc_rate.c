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
struct lpc32xx_clk {int /*<<< orphan*/  reg; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_regmap ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 struct lpc32xx_clk* to_lpc32xx_clk (struct clk_hw*) ; 

__attribute__((used)) static unsigned long lpc32xx_clk_uart_recalc_rate(struct clk_hw *hw,
						  unsigned long parent_rate)
{
	struct lpc32xx_clk *clk = to_lpc32xx_clk(hw);
	u32 val, x, y;

	regmap_read(clk_regmap, clk->reg, &val);
	x = (val & 0xFF00) >> 8;
	y = val & 0xFF;

	if (x && y)
		return (parent_rate * x) / y;
	else
		return 0;
}