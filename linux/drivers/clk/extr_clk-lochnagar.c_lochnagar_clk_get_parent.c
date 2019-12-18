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
typedef  unsigned int u8 ;
struct regmap {int dummy; } ;
struct lochnagar_clk_priv {int /*<<< orphan*/  dev; struct regmap* regmap; } ;
struct lochnagar_clk {unsigned int src_mask; int /*<<< orphan*/  name; int /*<<< orphan*/  src_reg; struct lochnagar_clk_priv* priv; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 unsigned int clk_hw_get_num_parents (struct clk_hw*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 struct lochnagar_clk* lochnagar_hw_to_lclk (struct clk_hw*) ; 
 int regmap_read (struct regmap*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static u8 lochnagar_clk_get_parent(struct clk_hw *hw)
{
	struct lochnagar_clk *lclk = lochnagar_hw_to_lclk(hw);
	struct lochnagar_clk_priv *priv = lclk->priv;
	struct regmap *regmap = priv->regmap;
	unsigned int val;
	int ret;

	ret = regmap_read(regmap, lclk->src_reg, &val);
	if (ret < 0) {
		dev_dbg(priv->dev, "Failed to read parent of %s: %d\n",
			lclk->name, ret);
		return clk_hw_get_num_parents(hw);
	}

	val &= lclk->src_mask;

	return val;
}