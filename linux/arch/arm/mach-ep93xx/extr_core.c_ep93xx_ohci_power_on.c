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

/* Variables and functions */
 scalar_t__ IS_ERR (scalar_t__) ; 
 int PTR_ERR (scalar_t__) ; 
 int clk_enable (scalar_t__) ; 
 scalar_t__ devm_clk_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ep93xx_ohci_host_clock ; 

__attribute__((used)) static int ep93xx_ohci_power_on(struct platform_device *pdev)
{
	if (!ep93xx_ohci_host_clock) {
		ep93xx_ohci_host_clock = devm_clk_get(&pdev->dev, NULL);
		if (IS_ERR(ep93xx_ohci_host_clock))
			return PTR_ERR(ep93xx_ohci_host_clock);
	}

	return clk_enable(ep93xx_ohci_host_clock);
}