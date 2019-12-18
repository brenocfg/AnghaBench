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
typedef  int /*<<< orphan*/  suspend_state_t ;

/* Variables and functions */
 int ENXIO ; 
 int SUSP_MODE_STANDBY_SF ; 
 int /*<<< orphan*/  clear_bl_bit () ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  set_bl_bit () ; 
 int /*<<< orphan*/  sh_mobile_call_standby (int) ; 
 int sh_mobile_sleep_supported ; 

__attribute__((used)) static int sh_pm_enter(suspend_state_t state)
{
	if (!(sh_mobile_sleep_supported & SUSP_MODE_STANDBY_SF))
		return -ENXIO;

	local_irq_disable();
	set_bl_bit();
	sh_mobile_call_standby(SUSP_MODE_STANDBY_SF);
	local_irq_disable();
	clear_bl_bit();
	return 0;
}