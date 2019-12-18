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
struct watchdog_device {int dummy; } ;
struct mcs814x_wdt {int /*<<< orphan*/  lock; scalar_t__ regs; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ WDT_COUNT ; 
 scalar_t__ WDT_MAX_VALUE ; 
 unsigned int clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mcs814x_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int mcs814x_wdt_set_timeout(struct watchdog_device *dev,
				unsigned int new_timeout)
{
	struct mcs814x_wdt *wdt = watchdog_get_drvdata(dev);

	spin_lock(&wdt->lock);
	/* watchdog counts upward and rollover (0xfffffff -> 0)
	 * triggers the reboot
	 */
	writel_relaxed(WDT_MAX_VALUE - (new_timeout * clk_get_rate(wdt->clk)),
		wdt->regs + WDT_COUNT);
	spin_unlock(&wdt->lock);

	return 0;
}