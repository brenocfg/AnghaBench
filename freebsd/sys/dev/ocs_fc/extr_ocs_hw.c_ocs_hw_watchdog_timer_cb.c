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
typedef  int /*<<< orphan*/  ocs_hw_t ;

/* Variables and functions */
 int /*<<< orphan*/  ocs_hw_config_watchdog_timer (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
ocs_hw_watchdog_timer_cb(void *arg)
{
	ocs_hw_t *hw = (ocs_hw_t *)arg;

	ocs_hw_config_watchdog_timer(hw);
	return;
}