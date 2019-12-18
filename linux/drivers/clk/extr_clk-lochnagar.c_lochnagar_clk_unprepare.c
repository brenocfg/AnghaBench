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
struct regmap {int dummy; } ;
struct lochnagar_clk_priv {int /*<<< orphan*/  dev; struct regmap* regmap; } ;
struct lochnagar_clk {int /*<<< orphan*/  name; int /*<<< orphan*/  ena_mask; int /*<<< orphan*/  cfg_reg; struct lochnagar_clk_priv* priv; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct lochnagar_clk* lochnagar_hw_to_lclk (struct clk_hw*) ; 
 int regmap_update_bits (struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lochnagar_clk_unprepare(struct clk_hw *hw)
{
	struct lochnagar_clk *lclk = lochnagar_hw_to_lclk(hw);
	struct lochnagar_clk_priv *priv = lclk->priv;
	struct regmap *regmap = priv->regmap;
	int ret;

	ret = regmap_update_bits(regmap, lclk->cfg_reg, lclk->ena_mask, 0);
	if (ret < 0)
		dev_dbg(priv->dev, "Failed to unprepare %s: %d\n",
			lclk->name, ret);
}