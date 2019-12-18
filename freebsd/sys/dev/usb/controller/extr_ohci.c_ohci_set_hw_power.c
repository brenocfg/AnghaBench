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
struct ohci_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int OHCI_BLE ; 
 struct ohci_softc* OHCI_BUS2SC (struct usb_bus*) ; 
 int OHCI_CLE ; 
 int /*<<< orphan*/  OHCI_CONTROL ; 
 int OHCI_IE ; 
 int OHCI_PLE ; 
 int OREAD4 (struct ohci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OWRITE4 (struct ohci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int USB_HW_POWER_BULK ; 
 int USB_HW_POWER_CONTROL ; 
 int USB_HW_POWER_INTERRUPT ; 
 int USB_HW_POWER_ISOC ; 

__attribute__((used)) static void
ohci_set_hw_power(struct usb_bus *bus)
{
	struct ohci_softc *sc = OHCI_BUS2SC(bus);
	uint32_t temp;
	uint32_t flags;

	DPRINTF("\n");

	USB_BUS_LOCK(bus);

	flags = bus->hw_power_state;

	temp = OREAD4(sc, OHCI_CONTROL);
	temp &= ~(OHCI_PLE | OHCI_IE | OHCI_CLE | OHCI_BLE);

	if (flags & USB_HW_POWER_CONTROL)
		temp |= OHCI_CLE;

	if (flags & USB_HW_POWER_BULK)
		temp |= OHCI_BLE;

	if (flags & USB_HW_POWER_INTERRUPT)
		temp |= OHCI_PLE;

	if (flags & USB_HW_POWER_ISOC)
		temp |= OHCI_IE | OHCI_PLE;

	OWRITE4(sc, OHCI_CONTROL, temp);

	USB_BUS_UNLOCK(bus);

	return;
}