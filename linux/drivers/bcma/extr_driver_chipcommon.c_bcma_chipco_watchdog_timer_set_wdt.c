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
struct bcma_drv_cc {int dummy; } ;
struct bcm47xx_wdt {int dummy; } ;

/* Variables and functions */
 struct bcma_drv_cc* bcm47xx_wdt_get_drvdata (struct bcm47xx_wdt*) ; 
 int /*<<< orphan*/  bcma_chipco_watchdog_timer_set (struct bcma_drv_cc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 bcma_chipco_watchdog_timer_set_wdt(struct bcm47xx_wdt *wdt,
					      u32 ticks)
{
	struct bcma_drv_cc *cc = bcm47xx_wdt_get_drvdata(wdt);

	return bcma_chipco_watchdog_timer_set(cc, ticks);
}