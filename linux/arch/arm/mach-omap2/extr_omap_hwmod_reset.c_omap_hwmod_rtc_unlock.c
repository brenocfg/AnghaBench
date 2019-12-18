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
struct omap_hwmod {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_RTC_KICK0_REG ; 
 int /*<<< orphan*/  OMAP_RTC_KICK0_VALUE ; 
 int /*<<< orphan*/  OMAP_RTC_KICK1_REG ; 
 int /*<<< orphan*/  OMAP_RTC_KICK1_VALUE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  omap_hwmod_write (int /*<<< orphan*/ ,struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_rtc_wait_not_busy (struct omap_hwmod*) ; 

void omap_hwmod_rtc_unlock(struct omap_hwmod *oh)
{
	unsigned long flags;

	local_irq_save(flags);
	omap_rtc_wait_not_busy(oh);
	omap_hwmod_write(OMAP_RTC_KICK0_VALUE, oh, OMAP_RTC_KICK0_REG);
	omap_hwmod_write(OMAP_RTC_KICK1_VALUE, oh, OMAP_RTC_KICK1_REG);
	local_irq_restore(flags);
}