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
struct lpss_clk_data {char* name; struct clk* clk; } ;
struct clk {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct clk*) ; 
 int PTR_ERR (struct clk*) ; 
 struct clk* clk_register_fixed_rate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct lpss_clk_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct lpss_clk_data*) ; 

__attribute__((used)) static int lpt_clk_probe(struct platform_device *pdev)
{
	struct lpss_clk_data *drvdata;
	struct clk *clk;

	drvdata = devm_kzalloc(&pdev->dev, sizeof(*drvdata), GFP_KERNEL);
	if (!drvdata)
		return -ENOMEM;

	/* LPSS free running clock */
	drvdata->name = "lpss_clk";
	clk = clk_register_fixed_rate(&pdev->dev, drvdata->name, NULL,
				      0, 100000000);
	if (IS_ERR(clk))
		return PTR_ERR(clk);

	drvdata->clk = clk;
	platform_set_drvdata(pdev, drvdata);
	return 0;
}