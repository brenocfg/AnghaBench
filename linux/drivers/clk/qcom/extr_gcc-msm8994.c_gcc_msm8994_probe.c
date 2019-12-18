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
struct device {int dummy; } ;
struct platform_device {struct device dev; } ;
struct clk {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* devm_clk_register (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_msm8994_desc ; 
 int qcom_cc_probe (struct platform_device*,int /*<<< orphan*/ *) ; 
 TYPE_1__ xo ; 

__attribute__((used)) static int gcc_msm8994_probe(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct clk *clk;

	clk = devm_clk_register(dev, &xo.hw);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	return qcom_cc_probe(pdev, &gcc_msm8994_desc);
}