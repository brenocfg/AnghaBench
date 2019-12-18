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
 int /*<<< orphan*/  OMAP_RTC_KICK1_REG ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  omap_hwmod_write (int,struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_rtc_wait_not_busy (struct omap_hwmod*) ; 

void omap_hwmod_rtc_lock(struct omap_hwmod *oh)
{
	unsigned long flags;

	local_irq_save(flags);
	omap_rtc_wait_not_busy(oh);
	omap_hwmod_write(0x0, oh, OMAP_RTC_KICK0_REG);
	omap_hwmod_write(0x0, oh, OMAP_RTC_KICK1_REG);
	local_irq_restore(flags);
}