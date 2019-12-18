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
typedef  int uint32_t ;

/* Variables and functions */
 int AR934X_BOOTSTRAP_USB_MODE_DEVICE ; 
 int /*<<< orphan*/  AR934X_RESET_REG_BOOTSTRAP ; 
 int /*<<< orphan*/  AR934X_RESET_USBSUS_OVERRIDE ; 
 int /*<<< orphan*/  AR934X_RESET_USB_HOST ; 
 int /*<<< orphan*/  AR934X_RESET_USB_PHY ; 
 int /*<<< orphan*/  AR934X_RESET_USB_PHY_ANALOG ; 
 int ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  ar71xx_device_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_device_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ar934x_chip_init_usb_peripheral(void)
{
	uint32_t reg;

	reg = ATH_READ_REG(AR934X_RESET_REG_BOOTSTRAP);
	if (reg & AR934X_BOOTSTRAP_USB_MODE_DEVICE)
		return;

	ar71xx_device_stop(AR934X_RESET_USBSUS_OVERRIDE);
	DELAY(100);

	ar71xx_device_start(AR934X_RESET_USB_PHY);
	DELAY(100);

	ar71xx_device_start(AR934X_RESET_USB_PHY_ANALOG);
	DELAY(100);

	ar71xx_device_start(AR934X_RESET_USB_HOST);
	DELAY(100);
}