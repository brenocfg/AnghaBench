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
struct usb2_clock_sel_priv {int /*<<< orphan*/  hw; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct platform_device {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_hw_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_clk_del_provider (int /*<<< orphan*/ ) ; 
 struct usb2_clock_sel_priv* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put (struct device*) ; 

__attribute__((used)) static int rcar_usb2_clock_sel_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;
	struct usb2_clock_sel_priv *priv = platform_get_drvdata(pdev);

	of_clk_del_provider(dev->of_node);
	clk_hw_unregister(&priv->hw);
	pm_runtime_put(dev);
	pm_runtime_disable(dev);

	return 0;
}