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
struct platform_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  read; int /*<<< orphan*/  init; int /*<<< orphan*/  name; } ;
struct imx_rngc {int /*<<< orphan*/  clk; TYPE_1__ rng; int /*<<< orphan*/ * dev; int /*<<< orphan*/  rng_op_done; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct imx_rngc* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int hwrng_register (TYPE_1__*) ; 
 int /*<<< orphan*/  imx_rngc_init ; 
 int /*<<< orphan*/  imx_rngc_irq ; 
 int /*<<< orphan*/  imx_rngc_irq_mask_clear (struct imx_rngc*) ; 
 int /*<<< orphan*/  imx_rngc_read ; 
 int imx_rngc_self_test (struct imx_rngc*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct imx_rngc*) ; 
 scalar_t__ self_test ; 

__attribute__((used)) static int imx_rngc_probe(struct platform_device *pdev)
{
	struct imx_rngc *rngc;
	int ret;
	int irq;

	rngc = devm_kzalloc(&pdev->dev, sizeof(*rngc), GFP_KERNEL);
	if (!rngc)
		return -ENOMEM;

	rngc->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(rngc->base))
		return PTR_ERR(rngc->base);

	rngc->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(rngc->clk)) {
		dev_err(&pdev->dev, "Can not get rng_clk\n");
		return PTR_ERR(rngc->clk);
	}

	irq = platform_get_irq(pdev, 0);
	if (irq <= 0) {
		dev_err(&pdev->dev, "Couldn't get irq %d\n", irq);
		return irq;
	}

	ret = clk_prepare_enable(rngc->clk);
	if (ret)
		return ret;

	ret = devm_request_irq(&pdev->dev,
			irq, imx_rngc_irq, 0, pdev->name, (void *)rngc);
	if (ret) {
		dev_err(rngc->dev, "Can't get interrupt working.\n");
		goto err;
	}

	init_completion(&rngc->rng_op_done);

	rngc->rng.name = pdev->name;
	rngc->rng.init = imx_rngc_init;
	rngc->rng.read = imx_rngc_read;

	rngc->dev = &pdev->dev;
	platform_set_drvdata(pdev, rngc);

	imx_rngc_irq_mask_clear(rngc);

	if (self_test) {
		ret = imx_rngc_self_test(rngc);
		if (ret) {
			dev_err(rngc->dev, "FSL RNGC self test failed.\n");
			goto err;
		}
	}

	ret = hwrng_register(&rngc->rng);
	if (ret) {
		dev_err(&pdev->dev, "FSL RNGC registering failed (%d)\n", ret);
		goto err;
	}

	dev_info(&pdev->dev, "Freescale RNGC registered.\n");
	return 0;

err:
	clk_disable_unprepare(rngc->clk);

	return ret;
}