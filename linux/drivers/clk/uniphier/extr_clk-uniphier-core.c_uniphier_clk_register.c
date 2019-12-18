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
struct TYPE_2__ {int /*<<< orphan*/  mux; int /*<<< orphan*/  gate; int /*<<< orphan*/  rate; int /*<<< orphan*/  factor; int /*<<< orphan*/  cpugear; } ;
struct uniphier_clk_data {int type; TYPE_1__ data; int /*<<< orphan*/  name; } ;
struct regmap {int dummy; } ;
struct device {int dummy; } ;
struct clk_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct clk_hw* ERR_PTR (int /*<<< orphan*/ ) ; 
#define  UNIPHIER_CLK_TYPE_CPUGEAR 132 
#define  UNIPHIER_CLK_TYPE_FIXED_FACTOR 131 
#define  UNIPHIER_CLK_TYPE_FIXED_RATE 130 
#define  UNIPHIER_CLK_TYPE_GATE 129 
#define  UNIPHIER_CLK_TYPE_MUX 128 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct clk_hw* uniphier_clk_register_cpugear (struct device*,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_hw* uniphier_clk_register_fixed_factor (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_hw* uniphier_clk_register_fixed_rate (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_hw* uniphier_clk_register_gate (struct device*,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_hw* uniphier_clk_register_mux (struct device*,struct regmap*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct clk_hw *uniphier_clk_register(struct device *dev,
					    struct regmap *regmap,
					const struct uniphier_clk_data *data)
{
	switch (data->type) {
	case UNIPHIER_CLK_TYPE_CPUGEAR:
		return uniphier_clk_register_cpugear(dev, regmap, data->name,
						     &data->data.cpugear);
	case UNIPHIER_CLK_TYPE_FIXED_FACTOR:
		return uniphier_clk_register_fixed_factor(dev, data->name,
							  &data->data.factor);
	case UNIPHIER_CLK_TYPE_FIXED_RATE:
		return uniphier_clk_register_fixed_rate(dev, data->name,
							&data->data.rate);
	case UNIPHIER_CLK_TYPE_GATE:
		return uniphier_clk_register_gate(dev, regmap, data->name,
						  &data->data.gate);
	case UNIPHIER_CLK_TYPE_MUX:
		return uniphier_clk_register_mux(dev, regmap, data->name,
						 &data->data.mux);
	default:
		dev_err(dev, "unsupported clock type\n");
		return ERR_PTR(-EINVAL);
	}
}