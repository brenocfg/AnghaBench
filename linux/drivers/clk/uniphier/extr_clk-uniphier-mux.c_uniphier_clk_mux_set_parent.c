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
typedef  size_t u8 ;
struct uniphier_clk_mux {int /*<<< orphan*/ * vals; int /*<<< orphan*/ * masks; int /*<<< orphan*/  reg; int /*<<< orphan*/  regmap; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int regmap_write_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct uniphier_clk_mux* to_uniphier_clk_mux (struct clk_hw*) ; 

__attribute__((used)) static int uniphier_clk_mux_set_parent(struct clk_hw *hw, u8 index)
{
	struct uniphier_clk_mux *mux = to_uniphier_clk_mux(hw);

	return regmap_write_bits(mux->regmap, mux->reg, mux->masks[index],
				 mux->vals[index]);
}