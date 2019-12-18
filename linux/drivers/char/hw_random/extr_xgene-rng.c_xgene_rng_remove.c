#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xgene_rng_dev {int /*<<< orphan*/  clk; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 int device_init_wakeup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct xgene_rng_dev* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int xgene_rng_remove(struct platform_device *pdev)
{
	struct xgene_rng_dev *ctx = platform_get_drvdata(pdev);
	int rc;

	rc = device_init_wakeup(&pdev->dev, 0);
	if (rc)
		dev_err(&pdev->dev, "RNG init wakeup failed error %d\n", rc);
	if (!IS_ERR(ctx->clk))
		clk_disable_unprepare(ctx->clk);

	return rc;
}