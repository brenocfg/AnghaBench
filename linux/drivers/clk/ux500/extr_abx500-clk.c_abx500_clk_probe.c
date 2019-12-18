#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct platform_device {TYPE_1__ dev; } ;
struct ab8500 {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ab8500_reg_clks (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 struct ab8500* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 scalar_t__ is_ab8500 (struct ab8500*) ; 
 scalar_t__ is_ab8505 (struct ab8500*) ; 

__attribute__((used)) static int abx500_clk_probe(struct platform_device *pdev)
{
	struct ab8500 *parent = dev_get_drvdata(pdev->dev.parent);
	int ret;

	if (is_ab8500(parent) || is_ab8505(parent)) {
		ret = ab8500_reg_clks(&pdev->dev);
	} else {
		dev_err(&pdev->dev, "non supported plf id\n");
		return -ENODEV;
	}

	return ret;
}