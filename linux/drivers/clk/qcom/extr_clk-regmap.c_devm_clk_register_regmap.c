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
struct device {struct device* parent; } ;
struct clk_regmap {int /*<<< orphan*/  hw; void* regmap; } ;

/* Variables and functions */
 void* dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ *) ; 

int devm_clk_register_regmap(struct device *dev, struct clk_regmap *rclk)
{
	if (dev && dev_get_regmap(dev, NULL))
		rclk->regmap = dev_get_regmap(dev, NULL);
	else if (dev && dev->parent)
		rclk->regmap = dev_get_regmap(dev->parent, NULL);

	return devm_clk_hw_register(dev, &rclk->hw);
}