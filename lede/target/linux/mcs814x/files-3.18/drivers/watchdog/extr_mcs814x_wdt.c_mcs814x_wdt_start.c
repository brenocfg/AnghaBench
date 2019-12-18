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
typedef  int /*<<< orphan*/  u32 ;
struct watchdog_device {int dummy; } ;
struct mcs814x_wdt {int /*<<< orphan*/  lock; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ WDT_CTRL ; 
 int /*<<< orphan*/  WDT_CTRL_EN ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct mcs814x_wdt* watchdog_get_drvdata (struct watchdog_device*) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int mcs814x_wdt_start(struct watchdog_device *dev)
{
	struct mcs814x_wdt *wdt = watchdog_get_drvdata(dev);
	u32 reg;

	spin_lock(&wdt->lock);
	reg = readl_relaxed(wdt->regs + WDT_CTRL);
	reg |= WDT_CTRL_EN;
	writel_relaxed(reg, wdt->regs + WDT_CTRL);
	spin_unlock(&wdt->lock);

	return 0;
}