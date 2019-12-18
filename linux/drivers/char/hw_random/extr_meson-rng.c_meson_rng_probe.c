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
struct resource {int dummy; } ;
struct device {int dummy; } ;
struct platform_device {int /*<<< orphan*/  name; struct device dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct meson_rng_data {TYPE_1__ rng; int /*<<< orphan*/ * core_clk; int /*<<< orphan*/ * base; struct platform_device* pdev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int devm_add_action_or_reset (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_clk_get (struct device*,char*) ; 
 int devm_hwrng_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 struct meson_rng_data* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  meson_rng_clk_disable ; 
 int /*<<< orphan*/  meson_rng_read ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct meson_rng_data*) ; 

__attribute__((used)) static int meson_rng_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct meson_rng_data *data;
	struct resource *res;
	int ret;

	data = devm_kzalloc(dev, sizeof(*data), GFP_KERNEL);
	if (!data)
		return -ENOMEM;

	data->pdev = pdev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	data->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(data->base))
		return PTR_ERR(data->base);

	data->core_clk = devm_clk_get(dev, "core");
	if (IS_ERR(data->core_clk))
		data->core_clk = NULL;

	if (data->core_clk) {
		ret = clk_prepare_enable(data->core_clk);
		if (ret)
			return ret;
		ret = devm_add_action_or_reset(dev, meson_rng_clk_disable,
					       data->core_clk);
		if (ret)
			return ret;
	}

	data->rng.name = pdev->name;
	data->rng.read = meson_rng_read;

	platform_set_drvdata(pdev, data);

	return devm_hwrng_register(dev, &data->rng);
}