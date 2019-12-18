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
struct omap_ehci_softc {int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ EHCI_HCD_OMAP_MODE_PHY ; 
 int OMAP_HS_USB_PORTS ; 
 int /*<<< orphan*/  OMAP_USBHOST_USBCMD ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int omap_ehci_read_4 (struct omap_ehci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap_ehci_soft_phy_reset (struct omap_ehci_softc*,int) ; 
 int /*<<< orphan*/  omap_ehci_write_4 (struct omap_ehci_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ omap_usb_port_mode (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
omap_ehci_init(struct omap_ehci_softc *isc)
{
	uint32_t reg = 0;
	int i;
	device_t uhh_dev;
	
	uhh_dev = device_get_parent(isc->sc_dev);
	device_printf(isc->sc_dev, "Starting TI EHCI USB Controller\n");

	/* Set the interrupt threshold control, it controls the maximum rate at
	 * which the host controller issues interrupts.  We set it to 1 microframe
	 * at startup - the default is 8 mircoframes (equates to 1ms).
	 */
	reg = omap_ehci_read_4(isc, OMAP_USBHOST_USBCMD);
	reg &= 0xff00ffff;
	reg |= (1 << 16);
	omap_ehci_write_4(isc, OMAP_USBHOST_USBCMD, reg);

	/* Soft reset the PHY using PHY reset command over ULPI */
	for (i = 0; i < OMAP_HS_USB_PORTS; i++) {
		if (omap_usb_port_mode(uhh_dev, i) == EHCI_HCD_OMAP_MODE_PHY)
			omap_ehci_soft_phy_reset(isc, i);

	}

	return(0);
}