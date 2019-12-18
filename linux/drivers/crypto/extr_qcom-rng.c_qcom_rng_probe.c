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
struct qcom_rng {unsigned long skip_init; int /*<<< orphan*/  clk; int /*<<< orphan*/  base; int /*<<< orphan*/  lock; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int crypto_register_rng (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ device_get_match_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_clk_get (int /*<<< orphan*/ *,char*) ; 
 struct qcom_rng* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_platform_ioremap_resource (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  has_acpi_companion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct qcom_rng*) ; 
 int /*<<< orphan*/  qcom_rng_alg ; 
 struct qcom_rng* qcom_rng_dev ; 

__attribute__((used)) static int qcom_rng_probe(struct platform_device *pdev)
{
	struct qcom_rng *rng;
	int ret;

	rng = devm_kzalloc(&pdev->dev, sizeof(*rng), GFP_KERNEL);
	if (!rng)
		return -ENOMEM;

	platform_set_drvdata(pdev, rng);
	mutex_init(&rng->lock);

	rng->base = devm_platform_ioremap_resource(pdev, 0);
	if (IS_ERR(rng->base))
		return PTR_ERR(rng->base);

	/* ACPI systems have clk already on, so skip clk_get */
	if (!has_acpi_companion(&pdev->dev)) {
		rng->clk = devm_clk_get(&pdev->dev, "core");
		if (IS_ERR(rng->clk))
			return PTR_ERR(rng->clk);
	}


	rng->skip_init = (unsigned long)device_get_match_data(&pdev->dev);

	qcom_rng_dev = rng;
	ret = crypto_register_rng(&qcom_rng_alg);
	if (ret) {
		dev_err(&pdev->dev, "Register crypto rng failed: %d\n", ret);
		qcom_rng_dev = NULL;
	}

	return ret;
}