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
struct device {scalar_t__ of_node; } ;
struct platform_device {struct device dev; } ;
struct TYPE_2__ {int quality; unsigned long priv; int /*<<< orphan*/  name; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  init; int /*<<< orphan*/  read; } ;
struct omap_rng_dev {int /*<<< orphan*/ * clk; int /*<<< orphan*/ * clk_reg; int /*<<< orphan*/ * base; TYPE_1__ rng; struct device* dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EPROBE_DEFER ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 int PTR_ERR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RNG_REV_REG ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ *) ; 
 int clk_prepare_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  dev_info (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 void* devm_clk_get (struct device*,char*) ; 
 int devm_hwrng_register (struct device*,TYPE_1__*) ; 
 int /*<<< orphan*/ * devm_ioremap_resource (struct device*,struct resource*) ; 
 int /*<<< orphan*/  devm_kstrdup (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct omap_rng_dev* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int get_omap_rng_device_details (struct omap_rng_dev*) ; 
 int of_get_omap_rng_device_details (struct omap_rng_dev*,struct platform_device*) ; 
 int /*<<< orphan*/  omap_rng_cleanup ; 
 int /*<<< orphan*/  omap_rng_do_read ; 
 int /*<<< orphan*/  omap_rng_init ; 
 int /*<<< orphan*/  omap_rng_read (struct omap_rng_dev*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct omap_rng_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_enable (struct device*) ; 
 int pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 

__attribute__((used)) static int omap_rng_probe(struct platform_device *pdev)
{
	struct omap_rng_dev *priv;
	struct resource *res;
	struct device *dev = &pdev->dev;
	int ret;

	priv = devm_kzalloc(dev, sizeof(struct omap_rng_dev), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->rng.read = omap_rng_do_read;
	priv->rng.init = omap_rng_init;
	priv->rng.cleanup = omap_rng_cleanup;
	priv->rng.quality = 900;

	priv->rng.priv = (unsigned long)priv;
	platform_set_drvdata(pdev, priv);
	priv->dev = dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	priv->base = devm_ioremap_resource(dev, res);
	if (IS_ERR(priv->base)) {
		ret = PTR_ERR(priv->base);
		goto err_ioremap;
	}

	priv->rng.name = devm_kstrdup(dev, dev_name(dev), GFP_KERNEL);
	if (!priv->rng.name) {
		ret = -ENOMEM;
		goto err_ioremap;
	}

	pm_runtime_enable(&pdev->dev);
	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Failed to runtime_get device: %d\n", ret);
		pm_runtime_put_noidle(&pdev->dev);
		goto err_ioremap;
	}

	priv->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(priv->clk) && PTR_ERR(priv->clk) == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (!IS_ERR(priv->clk)) {
		ret = clk_prepare_enable(priv->clk);
		if (ret) {
			dev_err(&pdev->dev,
				"Unable to enable the clk: %d\n", ret);
			goto err_register;
		}
	}

	priv->clk_reg = devm_clk_get(&pdev->dev, "reg");
	if (IS_ERR(priv->clk_reg) && PTR_ERR(priv->clk_reg) == -EPROBE_DEFER)
		return -EPROBE_DEFER;
	if (!IS_ERR(priv->clk_reg)) {
		ret = clk_prepare_enable(priv->clk_reg);
		if (ret) {
			dev_err(&pdev->dev,
				"Unable to enable the register clk: %d\n",
				ret);
			goto err_register;
		}
	}

	ret = (dev->of_node) ? of_get_omap_rng_device_details(priv, pdev) :
				get_omap_rng_device_details(priv);
	if (ret)
		goto err_register;

	ret = devm_hwrng_register(&pdev->dev, &priv->rng);
	if (ret)
		goto err_register;

	dev_info(&pdev->dev, "Random Number Generator ver. %02x\n",
		 omap_rng_read(priv, RNG_REV_REG));

	return 0;

err_register:
	priv->base = NULL;
	pm_runtime_put_sync(&pdev->dev);
	pm_runtime_disable(&pdev->dev);

	clk_disable_unprepare(priv->clk_reg);
	clk_disable_unprepare(priv->clk);
err_ioremap:
	dev_err(dev, "initialization failed.\n");
	return ret;
}