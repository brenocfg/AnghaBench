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
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eemi_ops ; 
 int zynqmp_clk_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynqmp_pm_get_eemi_ops () ; 

__attribute__((used)) static int zynqmp_clock_probe(struct platform_device *pdev)
{
	int ret;
	struct device *dev = &pdev->dev;

	eemi_ops = zynqmp_pm_get_eemi_ops();
	if (IS_ERR(eemi_ops))
		return PTR_ERR(eemi_ops);

	ret = zynqmp_clk_setup(dev->of_node);

	return ret;
}