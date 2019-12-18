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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS5536_PM_RTC ; 
 int /*<<< orphan*/  olpc_xo1_pm_wakeup_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rtc_wake_on(struct device *dev)
{
	olpc_xo1_pm_wakeup_set(CS5536_PM_RTC);
}