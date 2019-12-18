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
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 
 int /*<<< orphan*/  S3C2410_GPG (int) ; 
 int /*<<< orphan*/  gpio_set_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void n30_sdi_set_power(unsigned char power_mode, unsigned short vdd)
{
	switch (power_mode) {
	case MMC_POWER_ON:
	case MMC_POWER_UP:
		gpio_set_value(S3C2410_GPG(4), 1);
		break;
	case MMC_POWER_OFF:
	default:
		gpio_set_value(S3C2410_GPG(4), 0);
		break;
	}
}