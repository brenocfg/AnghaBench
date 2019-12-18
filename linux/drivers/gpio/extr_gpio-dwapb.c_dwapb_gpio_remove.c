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
struct dwapb_gpio {int /*<<< orphan*/  clk; int /*<<< orphan*/  rst; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_disable_unprepare (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dwapb_gpio_unregister (struct dwapb_gpio*) ; 
 int /*<<< orphan*/  dwapb_irq_teardown (struct dwapb_gpio*) ; 
 struct dwapb_gpio* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reset_control_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dwapb_gpio_remove(struct platform_device *pdev)
{
	struct dwapb_gpio *gpio = platform_get_drvdata(pdev);

	dwapb_gpio_unregister(gpio);
	dwapb_irq_teardown(gpio);
	reset_control_assert(gpio->rst);
	clk_disable_unprepare(gpio->clk);

	return 0;
}