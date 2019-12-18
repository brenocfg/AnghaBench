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
 int /*<<< orphan*/  PMAC_FTR_READ_GPIO ; 
 int /*<<< orphan*/  PMAC_FTR_WRITE_GPIO ; 
 int /*<<< orphan*/  debug_calc_bogomips () ; 
 int /*<<< orphan*/  frequency_gpio ; 
 int /*<<< orphan*/  local_delay (int) ; 
 int pmac_call_feature (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  slew_done_gpio ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  voltage_gpio ; 

__attribute__((used)) static int gpios_set_cpu_speed(int low_speed)
{
	int gpio, timeout = 0;

	/* If ramping up, set voltage first */
	if (low_speed == 0) {
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, voltage_gpio, 0x05);
		/* Delay is way too big but it's ok, we schedule */
		local_delay(10);
	}

	/* Set frequency */
	gpio = 	pmac_call_feature(PMAC_FTR_READ_GPIO, NULL, frequency_gpio, 0);
	if (low_speed == ((gpio & 0x01) == 0))
		goto skip;

	pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, frequency_gpio,
			  low_speed ? 0x04 : 0x05);
	udelay(200);
	do {
		if (++timeout > 100)
			break;
		local_delay(1);
		gpio = pmac_call_feature(PMAC_FTR_READ_GPIO, NULL, slew_done_gpio, 0);
	} while((gpio & 0x02) == 0);
 skip:
	/* If ramping down, set voltage last */
	if (low_speed == 1) {
		pmac_call_feature(PMAC_FTR_WRITE_GPIO, NULL, voltage_gpio, 0x04);
		/* Delay is way too big but it's ok, we schedule */
		local_delay(10);
	}

#ifdef DEBUG_FREQ
	debug_calc_bogomips();
#endif

	return 0;
}