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
 int /*<<< orphan*/  OMAP_TIMER_CTRL_ST ; 
 int /*<<< orphan*/  OMAP_TIMER_POSTED ; 
 int /*<<< orphan*/  __omap_dm_timer_load_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkev ; 

__attribute__((used)) static int omap2_gp_timer_set_next_event(unsigned long cycles,
					 struct clock_event_device *evt)
{
	__omap_dm_timer_load_start(&clkev, OMAP_TIMER_CTRL_ST,
				   0xffffffff - cycles, OMAP_TIMER_POSTED);

	return 0;
}