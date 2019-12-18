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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_READ_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  QCA953X_RESET_REG_BOOTSTRAP ; 
 int /*<<< orphan*/  QCA953X_RESET_USBSUS_OVERRIDE ; 
 int /*<<< orphan*/  QCA953X_RESET_USB_HOST ; 
 int /*<<< orphan*/  QCA953X_RESET_USB_PHY ; 
 int /*<<< orphan*/  QCA953X_RESET_USB_PHY_ANALOG ; 
 int /*<<< orphan*/  ar71xx_device_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ar71xx_device_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qca953x_chip_init_usb_peripheral(void)
{
	uint32_t bootstrap;

	bootstrap = ATH_READ_REG(QCA953X_RESET_REG_BOOTSTRAP);

	ar71xx_device_stop(QCA953X_RESET_USBSUS_OVERRIDE);
	DELAY(1000);

	ar71xx_device_start(QCA953X_RESET_USB_PHY);
	DELAY(1000);

	ar71xx_device_start(QCA953X_RESET_USB_PHY_ANALOG);
	DELAY(1000);

	ar71xx_device_start(QCA953X_RESET_USB_HOST);
	DELAY(1000);
}