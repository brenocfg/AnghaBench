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
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int pm_clk_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pm_clk_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_clk_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_enable (int /*<<< orphan*/ *) ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  turingcc_desc ; 

__attribute__((used)) static int turingcc_probe(struct platform_device *pdev)
{
	int ret;

	pm_runtime_enable(&pdev->dev);
	ret = pm_clk_create(&pdev->dev);
	if (ret)
		goto disable_pm_runtime;

	ret = pm_clk_add(&pdev->dev, NULL);
	if (ret < 0) {
		dev_err(&pdev->dev, "failed to acquire iface clock\n");
		goto destroy_pm_clk;
	}

	ret = qcom_cc_probe(pdev, &turingcc_desc);
	if (ret < 0)
		goto destroy_pm_clk;

	return 0;

destroy_pm_clk:
	pm_clk_destroy(&pdev->dev);

disable_pm_runtime:
	pm_runtime_disable(&pdev->dev);

	return ret;
}