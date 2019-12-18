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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {unsigned long priv; int /*<<< orphan*/  read; int /*<<< orphan*/  init; int /*<<< orphan*/  name; } ;
struct exynos_trng_dev {int /*<<< orphan*/  clk; TYPE_1__ rng; int /*<<< orphan*/  mem; int /*<<< orphan*/ * dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 int /*<<< orphan*/  devm_kstrdup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct exynos_trng_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exynos_trng_do_read ; 
 int /*<<< orphan*/  exynos_trng_init ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct exynos_trng_dev*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int exynos_trng_probe(struct platform_device *pdev)
{
	struct exynos_trng_dev *trng;
	struct resource *res;
	int ret = -ENOMEM;

	trng = devm_kzalloc(&pdev->dev, sizeof(*trng), GFP_KERNEL);
	if (!trng)
		return ret;

	trng->rng.name = devm_kstrdup(&pdev->dev, dev_name(&pdev->dev),
				      GFP_KERNEL);
	if (!trng->rng.name)
		return ret;

	trng->rng.init = exynos_trng_init;
	trng->rng.read = exynos_trng_do_read;
	trng->rng.priv = (unsigned long) trng;

	platform_set_drvdata(pdev, trng);
	trng->dev = &pdev->dev;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	trng->mem = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(trng->mem))
		return PTR_ERR(trng->mem);

	pm_runtime_enable(&pdev->dev);
	ret = pm_runtime_get_sync(&pdev->dev);
	if (ret < 0) {
		dev_err(&pdev->dev, "Could not get runtime PM.\n");
		goto err_pm_get;
	}

	trng->clk = devm_clk_get(&pdev->dev, "secss");
	if (IS_ERR(trng->clk)) {
		ret = PTR_ERR(trng->clk);
		dev_err(&pdev->dev, "Could not get clock.\n");
		goto err_clock;
	}

	ret = clk_prepare_enable(trng->clk);
	if (ret) {
		dev_err(&pdev->dev, "Could not enable the clk.\n");
		goto err_clock;
	}

	ret = devm_hwrng_register(&pdev->dev, &trng->rng);
	if (ret) {
		dev_err(&pdev->dev, "Could not register hwrng device.\n");
		goto err_register;
	}

	dev_info(&pdev->dev, "Exynos True Random Number Generator.\n");

	return 0;

err_register:
	clk_disable_unprepare(trng->clk);

err_clock:
	pm_runtime_put_sync(&pdev->dev);

err_pm_get:
	pm_runtime_disable(&pdev->dev);

	return ret;
}