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
struct platform_device {int dummy; } ;
struct clk_regmap_mux_div {int /*<<< orphan*/  clk_nb; int /*<<< orphan*/  pclk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_notifier_unregister (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct clk_regmap_mux_div* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int qcom_apcs_msm8916_clk_remove(struct platform_device *pdev)
{
	struct clk_regmap_mux_div *a53cc = platform_get_drvdata(pdev);

	clk_notifier_unregister(a53cc->pclk, &a53cc->clk_nb);

	return 0;
}