#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct meson_eeclkc_data {int regmap_clk_num; TYPE_2__* hw_onecell_data; TYPE_1__** regmap_clks; scalar_t__ init_count; int /*<<< orphan*/  init_regs; } ;
struct TYPE_4__ {int num; int /*<<< orphan*/ * hws; } ;
struct TYPE_3__ {struct regmap* map; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 struct meson_eeclkc_data* of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_multi_reg_write (struct regmap*,int /*<<< orphan*/ ,scalar_t__) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

int meson_eeclkc_probe(struct platform_device *pdev)
{
	const struct meson_eeclkc_data *data;
	struct device *dev = &pdev->dev;
	struct regmap *map;
	int ret, i;

	data = of_device_get_match_data(dev);
	if (!data)
		return -EINVAL;

	/* Get the hhi system controller node */
	map = syscon_node_to_regmap(of_get_parent(dev->of_node));
	if (IS_ERR(map)) {
		dev_err(dev,
			"failed to get HHI regmap\n");
		return PTR_ERR(map);
	}

	if (data->init_count)
		regmap_multi_reg_write(map, data->init_regs, data->init_count);

	/* Populate regmap for the regmap backed clocks */
	for (i = 0; i < data->regmap_clk_num; i++)
		data->regmap_clks[i]->map = map;

	for (i = 0; i < data->hw_onecell_data->num; i++) {
		/* array might be sparse */
		if (!data->hw_onecell_data->hws[i])
			continue;

		ret = devm_clk_hw_register(dev, data->hw_onecell_data->hws[i]);
		if (ret) {
			dev_err(dev, "Clock registration failed\n");
			return ret;
		}
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
					   data->hw_onecell_data);
}