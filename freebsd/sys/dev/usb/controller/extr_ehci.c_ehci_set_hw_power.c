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
struct usb_bus {int hw_power_state; } ;
typedef  int /*<<< orphan*/  ehci_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/ * EHCI_BUS2SC (struct usb_bus*) ; 
 int EHCI_CMD_ASE ; 
 int EHCI_CMD_PSE ; 
 int /*<<< orphan*/  EHCI_USBCMD ; 
 int EOREAD4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EOWRITE4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int USB_HW_POWER_BULK ; 
 int USB_HW_POWER_CONTROL ; 
 int USB_HW_POWER_INTERRUPT ; 
 int USB_HW_POWER_ISOC ; 

__attribute__((used)) static void
ehci_set_hw_power(struct usb_bus *bus)
{
	ehci_softc_t *sc = EHCI_BUS2SC(bus);
	uint32_t temp;
	uint32_t flags;

	DPRINTF("\n");

	USB_BUS_LOCK(bus);

	flags = bus->hw_power_state;

	temp = EOREAD4(sc, EHCI_USBCMD);

	temp &= ~(EHCI_CMD_ASE | EHCI_CMD_PSE);

	if (flags & (USB_HW_POWER_CONTROL |
	    USB_HW_POWER_BULK)) {
		DPRINTF("Async is active\n");
		temp |= EHCI_CMD_ASE;
	}
	if (flags & (USB_HW_POWER_INTERRUPT |
	    USB_HW_POWER_ISOC)) {
		DPRINTF("Periodic is active\n");
		temp |= EHCI_CMD_PSE;
	}
	EOWRITE4(sc, EHCI_USBCMD, temp);

	USB_BUS_UNLOCK(bus);

	return;
}