#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct rpm_smd_clk_desc {size_t num_clks; struct clk_smd_rpm** clks; } ;
struct rpm_cc {size_t num_clks; struct clk_smd_rpm** clks; } ;
struct qcom_smd_rpm {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct clk_smd_rpm {int /*<<< orphan*/  hw; struct qcom_smd_rpm* rpm; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int clk_smd_rpm_enable_scaling (struct qcom_smd_rpm*) ; 
 int clk_smd_rpm_handoff (struct clk_smd_rpm*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,...) ; 
 struct qcom_smd_rpm* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int devm_clk_hw_register (TYPE_1__*,int /*<<< orphan*/ *) ; 
 struct rpm_cc* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int devm_of_clk_add_hw_provider (TYPE_1__*,int /*<<< orphan*/ ,struct rpm_cc*) ; 
 struct rpm_smd_clk_desc* of_device_get_match_data (TYPE_1__*) ; 
 int /*<<< orphan*/  qcom_smdrpm_clk_hw_get ; 

__attribute__((used)) static int rpm_smd_clk_probe(struct platform_device *pdev)
{
	struct rpm_cc *rcc;
	int ret;
	size_t num_clks, i;
	struct qcom_smd_rpm *rpm;
	struct clk_smd_rpm **rpm_smd_clks;
	const struct rpm_smd_clk_desc *desc;

	rpm = dev_get_drvdata(pdev->dev.parent);
	if (!rpm) {
		dev_err(&pdev->dev, "Unable to retrieve handle to RPM\n");
		return -ENODEV;
	}

	desc = of_device_get_match_data(&pdev->dev);
	if (!desc)
		return -EINVAL;

	rpm_smd_clks = desc->clks;
	num_clks = desc->num_clks;

	rcc = devm_kzalloc(&pdev->dev, sizeof(*rcc), GFP_KERNEL);
	if (!rcc)
		return -ENOMEM;

	rcc->clks = rpm_smd_clks;
	rcc->num_clks = num_clks;

	for (i = 0; i < num_clks; i++) {
		if (!rpm_smd_clks[i])
			continue;

		rpm_smd_clks[i]->rpm = rpm;

		ret = clk_smd_rpm_handoff(rpm_smd_clks[i]);
		if (ret)
			goto err;
	}

	ret = clk_smd_rpm_enable_scaling(rpm);
	if (ret)
		goto err;

	for (i = 0; i < num_clks; i++) {
		if (!rpm_smd_clks[i])
			continue;

		ret = devm_clk_hw_register(&pdev->dev, &rpm_smd_clks[i]->hw);
		if (ret)
			goto err;
	}

	ret = devm_of_clk_add_hw_provider(&pdev->dev, qcom_smdrpm_clk_hw_get,
				     rcc);
	if (ret)
		goto err;

	return 0;
err:
	dev_err(&pdev->dev, "Error registering SMD clock driver (%d)\n", ret);
	return ret;
}