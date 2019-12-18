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
struct mcs814x_wdt {int /*<<< orphan*/  wdt_dev; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  clk_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct mcs814x_wdt*) ; 
 struct mcs814x_wdt* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  watchdog_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mcs814x_wdt_remove(struct platform_device *pdev)
{
	struct mcs814x_wdt *wdt = platform_get_drvdata(pdev);

	clk_put(wdt->clk);
	watchdog_unregister_device(&wdt->wdt_dev);
	watchdog_set_drvdata(&wdt->wdt_dev, NULL);
	kfree(wdt);
	platform_set_drvdata(pdev, NULL);

	return 0;
}