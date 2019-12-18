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
typedef  int /*<<< orphan*/  u32 ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int base; int /*<<< orphan*/  of_node; int /*<<< orphan*/  direction_output; int /*<<< orphan*/  set; int /*<<< orphan*/  ngpio; int /*<<< orphan*/  label; } ;
struct creg_gpio {TYPE_1__ gc; int /*<<< orphan*/  lock; int /*<<< orphan*/  layout; int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  creg_gpio_dir_out ; 
 int /*<<< orphan*/  creg_gpio_ids ; 
 int /*<<< orphan*/  creg_gpio_set ; 
 int creg_gpio_validate (struct device*,struct creg_gpio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int devm_gpiochip_add_data (struct device*,TYPE_1__*,struct creg_gpio*) ; 
 struct creg_gpio* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int creg_gpio_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct device *dev = &pdev->dev;
	struct creg_gpio *hcg;
	u32 ngpios;
	int ret;

	hcg = devm_kzalloc(dev, sizeof(struct creg_gpio), GFP_KERNEL);
	if (!hcg)
		return -ENOMEM;

	hcg->regs = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(hcg->regs))
		return PTR_ERR(hcg->regs);

	match = of_match_node(creg_gpio_ids, pdev->dev.of_node);
	hcg->layout = match->data;
	if (!hcg->layout)
		return -EINVAL;

	ret = of_property_read_u32(dev->of_node, "ngpios", &ngpios);
	if (ret)
		return ret;

	ret = creg_gpio_validate(dev, hcg, ngpios);
	if (ret)
		return ret;

	spin_lock_init(&hcg->lock);

	hcg->gc.label = dev_name(dev);
	hcg->gc.base = -1;
	hcg->gc.ngpio = ngpios;
	hcg->gc.set = creg_gpio_set;
	hcg->gc.direction_output = creg_gpio_dir_out;
	hcg->gc.of_node = dev->of_node;

	ret = devm_gpiochip_add_data(dev, &hcg->gc, hcg);
	if (ret)
		return ret;

	dev_info(dev, "GPIO controller with %d gpios probed\n", ngpios);

	return 0;
}