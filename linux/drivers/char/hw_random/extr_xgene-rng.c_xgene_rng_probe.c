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
struct xgene_rng_dev {int irq; int /*<<< orphan*/  clk; int /*<<< orphan*/  csr_base; int /*<<< orphan*/ * dev; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {unsigned long priv; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*) ; 
 int device_init_wakeup (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int devm_hwrng_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct xgene_rng_dev* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct xgene_rng_dev*) ; 
 int platform_get_irq (struct platform_device*,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct xgene_rng_dev*) ; 
 TYPE_1__ xgene_rng_func ; 
 int /*<<< orphan*/  xgene_rng_irq_handler ; 

__attribute__((used)) static int xgene_rng_probe(struct platform_device *pdev)
{
	struct resource *res;
	struct xgene_rng_dev *ctx;
	int rc = 0;

	ctx = devm_kzalloc(&pdev->dev, sizeof(*ctx), GFP_KERNEL);
	if (!ctx)
		return -ENOMEM;

	ctx->dev = &pdev->dev;
	platform_set_drvdata(pdev, ctx);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	ctx->csr_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(ctx->csr_base))
		return PTR_ERR(ctx->csr_base);

	rc = platform_get_irq(pdev, 0);
	if (rc < 0) {
		dev_err(&pdev->dev, "No IRQ resource\n");
		return rc;
	}
	ctx->irq = rc;

	dev_dbg(&pdev->dev, "APM X-Gene RNG BASE %p ALARM IRQ %d",
		ctx->csr_base, ctx->irq);

	rc = devm_request_irq(&pdev->dev, ctx->irq, xgene_rng_irq_handler, 0,
				dev_name(&pdev->dev), ctx);
	if (rc) {
		dev_err(&pdev->dev, "Could not request RNG alarm IRQ\n");
		return rc;
	}

	/* Enable IP clock */
	ctx->clk = devm_clk_get(&pdev->dev, NULL);
	if (IS_ERR(ctx->clk)) {
		dev_warn(&pdev->dev, "Couldn't get the clock for RNG\n");
	} else {
		rc = clk_prepare_enable(ctx->clk);
		if (rc) {
			dev_warn(&pdev->dev,
				 "clock prepare enable failed for RNG");
			return rc;
		}
	}

	xgene_rng_func.priv = (unsigned long) ctx;

	rc = devm_hwrng_register(&pdev->dev, &xgene_rng_func);
	if (rc) {
		dev_err(&pdev->dev, "RNG registering failed error %d\n", rc);
		if (!IS_ERR(ctx->clk))
			clk_disable_unprepare(ctx->clk);
		return rc;
	}

	rc = device_init_wakeup(&pdev->dev, 1);
	if (rc) {
		dev_err(&pdev->dev, "RNG device_init_wakeup failed error %d\n",
			rc);
		if (!IS_ERR(ctx->clk))
			clk_disable_unprepare(ctx->clk);
		return rc;
	}

	return 0;
}