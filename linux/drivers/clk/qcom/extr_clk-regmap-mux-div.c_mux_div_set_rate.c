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
struct clk_regmap_mux_div {int /*<<< orphan*/  src; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int __mux_div_set_rate_and_parent (struct clk_hw*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 struct clk_regmap_mux_div* to_clk_regmap_mux_div (struct clk_hw*) ; 

__attribute__((used)) static int mux_div_set_rate(struct clk_hw *hw,
			    unsigned long rate, unsigned long prate)
{
	struct clk_regmap_mux_div *md = to_clk_regmap_mux_div(hw);

	return __mux_div_set_rate_and_parent(hw, rate, prate, md->src);
}