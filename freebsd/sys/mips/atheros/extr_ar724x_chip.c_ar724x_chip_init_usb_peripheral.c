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
#define  AR71XX_SOC_AR7240 130 
#define  AR71XX_SOC_AR7241 129 
#define  AR71XX_SOC_AR7242 128 
 int /*<<< orphan*/  AR71XX_USB_CTRL_FLADJ ; 
 int AR724X_RESET_MODULE_USB_OHCI_DLL ; 
 int AR724X_RESET_USB_HOST ; 
 int AR724X_RESET_USB_PHY ; 
 int /*<<< orphan*/  ATH_WRITE_REG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int USB_CTRL_FLADJ_A0_SHIFT ; 
 int /*<<< orphan*/  ar71xx_device_start (int) ; 
 int /*<<< orphan*/  ar71xx_device_stop (int) ; 
 int ar71xx_soc ; 

__attribute__((used)) static void
ar724x_chip_init_usb_peripheral(void)
{

	switch (ar71xx_soc) {
	case AR71XX_SOC_AR7240:
		ar71xx_device_stop(AR724X_RESET_MODULE_USB_OHCI_DLL |
		    AR724X_RESET_USB_HOST);
		DELAY(1000);

		ar71xx_device_start(AR724X_RESET_MODULE_USB_OHCI_DLL |
		    AR724X_RESET_USB_HOST);
		DELAY(1000);

		/*
		 * WAR for HW bug. Here it adjusts the duration
		 * between two SOFS.
		 */
		ATH_WRITE_REG(AR71XX_USB_CTRL_FLADJ,
		    (3 << USB_CTRL_FLADJ_A0_SHIFT));

		break;

	case AR71XX_SOC_AR7241:
	case AR71XX_SOC_AR7242:
		ar71xx_device_start(AR724X_RESET_MODULE_USB_OHCI_DLL);
		DELAY(100);

		ar71xx_device_start(AR724X_RESET_USB_HOST);
		DELAY(100);

		ar71xx_device_start(AR724X_RESET_USB_PHY);
		DELAY(100);

		break;

	default:
		break;
	}
}