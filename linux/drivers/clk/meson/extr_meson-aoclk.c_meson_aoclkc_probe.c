#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; int /*<<< orphan*/  nr_resets; int /*<<< orphan*/ * ops; } ;
struct meson_aoclk_reset_controller {TYPE_3__ reset; struct regmap* regmap; struct meson_aoclk_data* data; } ;
struct meson_aoclk_data {int num_clks; TYPE_2__* hw_data; TYPE_1__** clks; int /*<<< orphan*/  num_reset; } ;
struct TYPE_5__ {int num; int /*<<< orphan*/ * hws; } ;
struct TYPE_4__ {struct regmap* map; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int devm_clk_hw_register (struct device*,int /*<<< orphan*/ ) ; 
 struct meson_aoclk_reset_controller* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,void*) ; 
 int devm_reset_controller_register (struct device*,TYPE_3__*) ; 
 int /*<<< orphan*/  meson_aoclk_reset_ops ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 scalar_t__ of_device_get_match_data (struct device*) ; 
 int /*<<< orphan*/  of_get_parent (int /*<<< orphan*/ ) ; 
 struct regmap* syscon_node_to_regmap (int /*<<< orphan*/ ) ; 

int meson_aoclkc_probe(struct platform_device *pdev)
{
	struct meson_aoclk_reset_controller *rstc;
	struct meson_aoclk_data *data;
	struct device *dev = &pdev->dev;
	struct regmap *regmap;
	int ret, clkid;

	data = (struct meson_aoclk_data *) of_device_get_match_data(dev);
	if (!data)
		return -ENODEV;

	rstc = devm_kzalloc(dev, sizeof(*rstc), GFP_KERNEL);
	if (!rstc)
		return -ENOMEM;

	regmap = syscon_node_to_regmap(of_get_parent(dev->of_node));
	if (IS_ERR(regmap)) {
		dev_err(dev, "failed to get regmap\n");
		return PTR_ERR(regmap);
	}

	/* Reset Controller */
	rstc->data = data;
	rstc->regmap = regmap;
	rstc->reset.ops = &meson_aoclk_reset_ops;
	rstc->reset.nr_resets = data->num_reset,
	rstc->reset.of_node = dev->of_node;
	ret = devm_reset_controller_register(dev, &rstc->reset);
	if (ret) {
		dev_err(dev, "failed to register reset controller\n");
		return ret;
	}

	/* Populate regmap */
	for (clkid = 0; clkid < data->num_clks; clkid++)
		data->clks[clkid]->map = regmap;

	/* Register all clks */
	for (clkid = 0; clkid < data->hw_data->num; clkid++) {
		if (!data->hw_data->hws[clkid])
			continue;

		ret = devm_clk_hw_register(dev, data->hw_data->hws[clkid]);
		if (ret) {
			dev_err(dev, "Clock registration failed\n");
			return ret;
		}
	}

	return devm_of_clk_add_hw_provider(dev, of_clk_hw_onecell_get,
		(void *) data->hw_data);
}