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
 int /*<<< orphan*/  PMAC_FTR_WRITE_GPIO ; 
 int /*<<< orphan*/  local_delay (int) ; 
 int /*<<< orphan*/  low_choose_7447a_dfs (int) ; 
 int /*<<< orphan*/  pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  voltage_gpio ; 

__attribute__((used)) static int dfs_set_cpu_speed(int low_speed)
{
	if (low_speed == 0) {
		/* ramping up, set voltage first */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, voltage_gpio, 0x05);
		/* Make sure we sleep for at least 1ms */
		local_delay(1);
	}

	/* set frequency */
#ifdef CONFIG_PPC_BOOK3S_32
	low_choose_7447a_dfs(low_speed);
#endif
	udelay(100);

	if (low_speed == 1) {
		/* ramping down, set voltage last */
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, voltage_gpio, 0x04);
		local_delay(1);
	}

	return 0;
}