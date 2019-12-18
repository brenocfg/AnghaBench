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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_msm8916_desc ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 int qcom_cc_register_board_clk (struct device*,char*,char*,int) ; 
 int qcom_cc_register_sleep_clk (struct device*) ; 

__attribute__((used)) static int gcc_msm8916_probe(struct platform_device *pdev)
{
	int ret;
	struct device *dev = &pdev->dev;

	ret = qcom_cc_register_board_clk(dev, "xo_board", "xo", 19200000);
	if (ret)
		return ret;

	ret = qcom_cc_register_sleep_clk(dev);
	if (ret)
		return ret;

	return qcom_cc_probe(pdev, &gcc_msm8916_desc);
}