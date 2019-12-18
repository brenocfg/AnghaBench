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

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  FW_FEATURE_OPAL ; 
 scalar_t__ IDLE_NO_OVERRIDE ; 
 int TICK_USEC ; 
 scalar_t__ cpuidle_disable ; 
 int /*<<< orphan*/  cpuidle_state_table ; 
 int default_snooze_timeout ; 
 scalar_t__ firmware_has_feature (int /*<<< orphan*/ ) ; 
 int max_idle_state ; 
 int powernv_add_idle_states () ; 
 int /*<<< orphan*/  powernv_states ; 
 int snooze_timeout_en ; 
 int tb_ticks_per_usec ; 

__attribute__((used)) static int powernv_idle_probe(void)
{
	if (cpuidle_disable != IDLE_NO_OVERRIDE)
		return -ENODEV;

	if (firmware_has_feature(FW_FEATURE_OPAL)) {
		cpuidle_state_table = powernv_states;
		/* Device tree can indicate more idle states */
		max_idle_state = powernv_add_idle_states();
		default_snooze_timeout = TICK_USEC * tb_ticks_per_usec;
		if (max_idle_state > 1)
			snooze_timeout_en = true;
 	} else
 		return -ENODEV;

	return 0;
}