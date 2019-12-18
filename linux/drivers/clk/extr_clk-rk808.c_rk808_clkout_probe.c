#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct clk_init_data* init; } ;
struct rk808_clkout {TYPE_4__ clkout2_hw; TYPE_4__ clkout1_hw; struct rk808* rk808; } ;
struct rk808 {int /*<<< orphan*/  variant; struct i2c_client* i2c; } ;
struct TYPE_5__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct TYPE_6__ {struct device_node* of_node; } ;
struct i2c_client {TYPE_2__ dev; } ;
struct device_node {int dummy; } ;
struct clk_init_data {char* name; int /*<<< orphan*/ * ops; scalar_t__ num_parents; int /*<<< orphan*/ * parent_names; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rk808* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_clk_hw_register (TYPE_2__*,TYPE_4__*) ; 
 struct rk808_clkout* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (TYPE_1__*,int /*<<< orphan*/ ,struct rk808_clkout*) ; 
 int /*<<< orphan*/  of_clk_rk808_get ; 
 int /*<<< orphan*/  of_property_read_string_index (struct device_node*,char*,int,char**) ; 
 int /*<<< orphan*/  rk808_clkout1_ops ; 
 int /*<<< orphan*/ * rkpmic_get_ops (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rk808_clkout_probe(struct platform_device *pdev)
{
	struct rk808 *rk808 = dev_get_drvdata(pdev->dev.parent);
	struct i2c_client *client = rk808->i2c;
	struct device_node *node = client->dev.of_node;
	struct clk_init_data init = {};
	struct rk808_clkout *rk808_clkout;
	int ret;

	rk808_clkout = devm_kzalloc(&client->dev,
				    sizeof(*rk808_clkout), GFP_KERNEL);
	if (!rk808_clkout)
		return -ENOMEM;

	rk808_clkout->rk808 = rk808;

	init.parent_names = NULL;
	init.num_parents = 0;
	init.name = "rk808-clkout1";
	init.ops = &rk808_clkout1_ops;
	rk808_clkout->clkout1_hw.init = &init;

	/* optional override of the clockname */
	of_property_read_string_index(node, "clock-output-names",
				      0, &init.name);

	ret = devm_clk_hw_register(&client->dev, &rk808_clkout->clkout1_hw);
	if (ret)
		return ret;

	init.name = "rk808-clkout2";
	init.ops = rkpmic_get_ops(rk808->variant);
	rk808_clkout->clkout2_hw.init = &init;

	/* optional override of the clockname */
	of_property_read_string_index(node, "clock-output-names",
				      1, &init.name);

	ret = devm_clk_hw_register(&client->dev, &rk808_clkout->clkout2_hw);
	if (ret)
		return ret;

	return devm_of_clk_add_hw_provider(&pdev->dev, of_clk_rk808_get,
					   rk808_clkout);
}