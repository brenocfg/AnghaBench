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
struct led_classdev {int dummy; } ;
typedef  enum led_brightness { ____Placeholder_led_brightness } led_brightness ;

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_RESET_GE1_PHY ; 
 int /*<<< orphan*/  ath79_device_reset_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_device_reset_set (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wndr3700_usb_led_set(struct led_classdev *cdev,
				 enum led_brightness brightness)
{
	if (brightness)
		ath79_device_reset_clear(AR71XX_RESET_GE1_PHY);
	else
		ath79_device_reset_set(AR71XX_RESET_GE1_PHY);
}