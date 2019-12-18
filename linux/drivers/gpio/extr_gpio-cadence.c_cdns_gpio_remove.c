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
struct cdns_gpio_chip {int /*<<< orphan*/  pclk; scalar_t__ regs; int /*<<< orphan*/  bypass_orig; } ;

/* Variables and functions */
 scalar_t__ CDNS_GPIO_BYPASS_MODE ; 
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 
 struct cdns_gpio_chip* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int cdns_gpio_remove(struct platform_device *pdev)
{
	struct cdns_gpio_chip *cgpio = platform_get_drvdata(pdev);

	iowrite32(cgpio->bypass_orig, cgpio->regs + CDNS_GPIO_BYPASS_MODE);
	clk_disable_unprepare(cgpio->pclk);

	return 0;
}