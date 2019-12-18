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
struct clock_event_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OMAP_TIMER_INT_OVERFLOW ; 
 int /*<<< orphan*/  __omap_dm_timer_int_enable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkev ; 
 int /*<<< orphan*/  clockevent_gpt_hwmod ; 
 int /*<<< orphan*/  omap_hwmod_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void omap_clkevt_unidle(struct clock_event_device *unused)
{
	if (!clockevent_gpt_hwmod)
		return;

	omap_hwmod_enable(clockevent_gpt_hwmod);
	__omap_dm_timer_int_enable(&clkev, OMAP_TIMER_INT_OVERFLOW);
}