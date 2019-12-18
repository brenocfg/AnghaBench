#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct regmap {int dummy; } ;
struct device {struct device* parent; } ;
struct platform_device {struct device dev; } ;
struct TYPE_7__ {int /*<<< orphan*/  notifier_call; } ;
struct TYPE_5__ {struct clk_init_data* init; } ;
struct TYPE_6__ {TYPE_1__ hw; struct regmap* regmap; } ;
struct clk_regmap_mux_div {int reg_offset; int hid_width; int src_width; int src_shift; TYPE_3__ clk_nb; int /*<<< orphan*/  pclk; TYPE_2__ clkr; int /*<<< orphan*/  parent_map; scalar_t__ hid_shift; } ;
struct clk_init_data {char* name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/  num_parents; int /*<<< orphan*/  parent_names; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CLK_SET_RATE_PARENT ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a53cc_notifier_cb ; 
 int clk_notifier_register (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  clk_regmap_mux_div_ops ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int) ; 
 struct regmap* dev_get_regmap (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (struct device*,int /*<<< orphan*/ *) ; 
 int devm_clk_register_regmap (struct device*,TYPE_2__*) ; 
 struct clk_regmap_mux_div* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (struct device*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  gpll0_a53cc ; 
 int /*<<< orphan*/  gpll0_a53cc_map ; 
 int /*<<< orphan*/  of_clk_hw_simple_get ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct clk_regmap_mux_div*) ; 

__attribute__((used)) static int qcom_apcs_msm8916_clk_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct device *parent = dev->parent;
	struct clk_regmap_mux_div *a53cc;
	struct regmap *regmap;
	struct clk_init_data init = { };
	int ret = -ENODEV;

	regmap = dev_get_regmap(parent, NULL);
	if (!regmap) {
		dev_err(dev, "failed to get regmap: %d\n", ret);
		return ret;
	}

	a53cc = devm_kzalloc(dev, sizeof(*a53cc), GFP_KERNEL);
	if (!a53cc)
		return -ENOMEM;

	init.name = "a53mux";
	init.parent_names = gpll0_a53cc;
	init.num_parents = ARRAY_SIZE(gpll0_a53cc);
	init.ops = &clk_regmap_mux_div_ops;
	init.flags = CLK_SET_RATE_PARENT;

	a53cc->clkr.hw.init = &init;
	a53cc->clkr.regmap = regmap;
	a53cc->reg_offset = 0x50;
	a53cc->hid_width = 5;
	a53cc->hid_shift = 0;
	a53cc->src_width = 3;
	a53cc->src_shift = 8;
	a53cc->parent_map = gpll0_a53cc_map;

	a53cc->pclk = devm_clk_get(parent, NULL);
	if (IS_ERR(a53cc->pclk)) {
		ret = PTR_ERR(a53cc->pclk);
		dev_err(dev, "failed to get clk: %d\n", ret);
		return ret;
	}

	a53cc->clk_nb.notifier_call = a53cc_notifier_cb;
	ret = clk_notifier_register(a53cc->pclk, &a53cc->clk_nb);
	if (ret) {
		dev_err(dev, "failed to register clock notifier: %d\n", ret);
		return ret;
	}

	ret = devm_clk_register_regmap(dev, &a53cc->clkr);
	if (ret) {
		dev_err(dev, "failed to register regmap clock: %d\n", ret);
		goto err;
	}

	ret = devm_of_clk_add_hw_provider(dev, of_clk_hw_simple_get,
					  &a53cc->clkr.hw);
	if (ret) {
		dev_err(dev, "failed to add clock provider: %d\n", ret);
		goto err;
	}

	platform_set_drvdata(pdev, a53cc);

	return 0;

err:
	clk_notifier_unregister(a53cc->pclk, &a53cc->clk_nb);
	return ret;
}