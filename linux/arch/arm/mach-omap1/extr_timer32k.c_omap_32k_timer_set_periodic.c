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
 int /*<<< orphan*/  OMAP_32K_TIMER_TICK_PERIOD ; 
 int /*<<< orphan*/  omap_32k_timer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_32k_timer_stop () ; 

__attribute__((used)) static int omap_32k_timer_set_periodic(struct clock_event_device *evt)
{
	omap_32k_timer_stop();
	omap_32k_timer_start(OMAP_32K_TIMER_TICK_PERIOD);
	return 0;
}