#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tegra_aconnect {void* apb2ape_clk; void* ape_clk; } ;
struct TYPE_8__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_set_drvdata (TYPE_1__*,struct tegra_aconnect*) ; 
 void* devm_clk_get (TYPE_1__*,char*) ; 
 struct tegra_aconnect* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_platform_populate (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  pm_runtime_enable (TYPE_1__*) ; 

__attribute__((used)) static int tegra_aconnect_probe(struct platform_device *pdev)
{
	struct tegra_aconnect *aconnect;

	if (!pdev->dev.of_node)
		return -EINVAL;

	aconnect = devm_kzalloc(&pdev->dev, sizeof(struct tegra_aconnect),
				GFP_KERNEL);
	if (!aconnect)
		return -ENOMEM;

	aconnect->ape_clk = devm_clk_get(&pdev->dev, "ape");
	if (IS_ERR(aconnect->ape_clk)) {
		dev_err(&pdev->dev, "Can't retrieve ape clock\n");
		return PTR_ERR(aconnect->ape_clk);
	}

	aconnect->apb2ape_clk = devm_clk_get(&pdev->dev, "apb2ape");
	if (IS_ERR(aconnect->apb2ape_clk)) {
		dev_err(&pdev->dev, "Can't retrieve apb2ape clock\n");
		return PTR_ERR(aconnect->apb2ape_clk);
	}

	dev_set_drvdata(&pdev->dev, aconnect);
	pm_runtime_enable(&pdev->dev);

	of_platform_populate(pdev->dev.of_node, NULL, NULL, &pdev->dev);

	dev_info(&pdev->dev, "Tegra ACONNECT bus registered\n");

	return 0;
}