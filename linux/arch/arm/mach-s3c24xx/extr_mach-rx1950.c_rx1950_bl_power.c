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
 int /*<<< orphan*/  S3C2410_GPB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S3C2410_GPB0_TOUT0 ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ndelay (int) ; 
 int /*<<< orphan*/  s3c_gpio_cfgpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rx1950_bl_power(int enable)
{
	static int enabled;
	if (enabled == enable)
		return;
	if (!enable) {
			gpio_direction_output(S3C2410_GPB(0), 0);
	} else {
			/* LED driver need a "push" to power on */
			gpio_direction_output(S3C2410_GPB(0), 1);
			/* Warm up backlight for one period of PWM.
			 * Without this trick its almost impossible to
			 * enable backlight with low brightness value
			 */
			ndelay(48000);
			s3c_gpio_cfgpin(S3C2410_GPB(0), S3C2410_GPB0_TOUT0);
	}
	enabled = enable;
}