#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct of_device_id {int /*<<< orphan*/ * data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * d; } ;
struct TYPE_3__ {int /*<<< orphan*/ * d; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct platform_device*) ; 
 int PTR_ERR (struct platform_device*) ; 
 int /*<<< orphan*/  gcc_apq8064_desc ; 
 int /*<<< orphan*/  gcc_msm8960_match_table ; 
 TYPE_2__ hfpll1 ; 
 int /*<<< orphan*/  hfpll1_8064_data ; 
 TYPE_1__ hfpll_l2 ; 
 int /*<<< orphan*/  hfpll_l2_8064_data ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,struct device*) ; 
 struct platform_device* platform_device_register_data (struct device*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct platform_device*) ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_register_board_clk (struct device*,char*,char*,int) ; 

__attribute__((used)) static int gcc_msm8960_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	const struct of_device_id *match;
	struct platform_device *tsens;
	int ret;

	match = of_match_device(gcc_msm8960_match_table, &pdev->dev);
	if (!match)
		return -EINVAL;

	ret = qcom_cc_register_board_clk(dev, "cxo_board", "cxo", 19200000);
	if (ret)
		return ret;

	ret = qcom_cc_register_board_clk(dev, "pxo_board", "pxo", 27000000);
	if (ret)
		return ret;

	ret = qcom_cc_probe(pdev, match->data);
	if (ret)
		return ret;

	if (match->data == &gcc_apq8064_desc) {
		hfpll1.d = &hfpll1_8064_data;
		hfpll_l2.d = &hfpll_l2_8064_data;
	}

	tsens = platform_device_register_data(&pdev->dev, "qcom-tsens", -1,
					      NULL, 0);
	if (IS_ERR(tsens))
		return PTR_ERR(tsens);

	platform_set_drvdata(pdev, tsens);

	return 0;
}