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
 int /*<<< orphan*/  AR933X_RESET_USBSUS_OVERRIDE ; 
 int /*<<< orphan*/  AR933X_RESET_USB_HOST ; 
 int /*<<< orphan*/  AR933X_RESET_USB_PHY ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ar71xx_device_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_device_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar933x_chip_init_usb_peripheral(void)
{
	ar71xx_device_stop(AR933X_RESET_USBSUS_OVERRIDE);
	DELAY(100);

	ar71xx_device_start(AR933X_RESET_USB_HOST);
	DELAY(100);

	ar71xx_device_start(AR933X_RESET_USB_PHY);
	DELAY(100);
}