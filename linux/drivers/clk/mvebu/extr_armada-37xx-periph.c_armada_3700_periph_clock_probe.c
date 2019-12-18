#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct device_node {int dummy; } ;
struct clk_periph_driver_data {TYPE_1__* hw_data; int /*<<< orphan*/  lock; int /*<<< orphan*/  reg; } ;
struct clk_periph_data {scalar_t__ name; } ;
struct clk_hw {int dummy; } ;
struct TYPE_3__ {int num; struct clk_hw** hws; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 scalar_t__ armada_3700_add_composite_clk (struct clk_periph_data const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct device*,struct clk_hw**) ; 
 int /*<<< orphan*/  clk_hw_unregister (struct clk_hw*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,scalar_t__) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hws ; 
 int of_clk_add_hw_provider (struct device_node*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  of_clk_hw_onecell_get ; 
 struct clk_periph_data* of_device_get_match_data (struct device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct clk_periph_driver_data*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int struct_size (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int armada_3700_periph_clock_probe(struct platform_device *pdev)
{
	struct clk_periph_driver_data *driver_data;
	struct device_node *np = pdev->dev.of_node;
	const struct clk_periph_data *data;
	struct device *dev = &pdev->dev;
	int num_periph = 0, i, ret;
	struct resource *res;

	data = of_device_get_match_data(dev);
	if (!data)
		return -ENODEV;

	while (data[num_periph].name)
		num_periph++;

	driver_data = devm_kzalloc(dev, sizeof(*driver_data), GFP_KERNEL);
	if (!driver_data)
		return -ENOMEM;

	driver_data->hw_data = devm_kzalloc(dev,
					    struct_size(driver_data->hw_data,
							hws, num_periph),
					    GFP_KERNEL);
	if (!driver_data->hw_data)
		return -ENOMEM;
	driver_data->hw_data->num = num_periph;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	driver_data->reg = devm_ioremap_resource(dev, res);
	if (IS_ERR(driver_data->reg))
		return PTR_ERR(driver_data->reg);

	spin_lock_init(&driver_data->lock);

	for (i = 0; i < num_periph; i++) {
		struct clk_hw **hw = &driver_data->hw_data->hws[i];
		if (armada_3700_add_composite_clk(&data[i], driver_data->reg,
						  &driver_data->lock, dev, hw))
			dev_err(dev, "Can't register periph clock %s\n",
				data[i].name);
	}

	ret = of_clk_add_hw_provider(np, of_clk_hw_onecell_get,
				     driver_data->hw_data);
	if (ret) {
		for (i = 0; i < num_periph; i++)
			clk_hw_unregister(driver_data->hw_data->hws[i]);
		return ret;
	}

	platform_set_drvdata(pdev, driver_data);
	return 0;
}