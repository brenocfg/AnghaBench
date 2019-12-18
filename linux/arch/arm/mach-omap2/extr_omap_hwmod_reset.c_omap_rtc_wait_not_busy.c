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
 int /*<<< orphan*/  OMAP_RTC_MAX_READY_TIME ; 
 int OMAP_RTC_STATUS_BUSY ; 
 int /*<<< orphan*/  OMAP_RTC_STATUS_REG ; 
 int omap_hwmod_read (struct omap_hwmod*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_test_timeout (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void omap_rtc_wait_not_busy(struct omap_hwmod *oh)
{
	int i;

	/* BUSY may stay active for 1/32768 second (~30 usec) */
	omap_test_timeout(omap_hwmod_read(oh, OMAP_RTC_STATUS_REG)
			  & OMAP_RTC_STATUS_BUSY, OMAP_RTC_MAX_READY_TIME, i);
	/* now we have ~15 microseconds to read/write various registers */
}