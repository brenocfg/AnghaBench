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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  name; } ;
struct atmel_trng {int /*<<< orphan*/  clk; TYPE_1__ rng; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atmel_trng_enable (struct atmel_trng*) ; 
 int /*<<< orphan*/  atmel_trng_read ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct atmel_trng* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct atmel_trng*) ; 

__attribute__((used)) static int atmel_trng_probe(struct platform_device *pdev)
{
	struct atmel_trng *trng;
	struct resource *res;
	int ret;

	trng = devm_kzalloc(&pdev->dev, sizeof(*trng), GFP_KERNEL);
	if (!trng)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	trng->base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(trng->base))
		return PTR_ERR(trng->base);

	trng->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(trng->clk))
		return PTR_ERR(trng->clk);

	ret = clk_prepare_enable(trng->clk);
	if (ret)
		return ret;

	atmel_trng_enable(trng);
	trng->rng.name = pdev->name;
	trng->rng.read = atmel_trng_read;

	ret = devm_hwrng_register(&pdev->dev, &trng->rng);
	if (ret)
		goto err_register;

	platform_set_drvdata(pdev, trng);

	return 0;

err_register:
	clk_disable_unprepare(trng->clk);
	return ret;
}