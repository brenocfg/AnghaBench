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
struct usb_bus {int dummy; } ;
struct avr32dci_softc {int dummy; } ;

/* Variables and functions */
 struct avr32dci_softc* AVR32_BUS2SC (struct usb_bus*) ; 
#define  USB_HW_POWER_RESUME 130 
#define  USB_HW_POWER_SHUTDOWN 129 
#define  USB_HW_POWER_SUSPEND 128 
 int /*<<< orphan*/  avr32dci_resume (struct avr32dci_softc*) ; 
 int /*<<< orphan*/  avr32dci_suspend (struct avr32dci_softc*) ; 
 int /*<<< orphan*/  avr32dci_uninit (struct avr32dci_softc*) ; 

__attribute__((used)) static void
avr32dci_set_hw_power_sleep(struct usb_bus *bus, uint32_t state)
{
	struct avr32dci_softc *sc = AVR32_BUS2SC(bus);

	switch (state) {
	case USB_HW_POWER_SUSPEND:
		avr32dci_suspend(sc);
		break;
	case USB_HW_POWER_SHUTDOWN:
		avr32dci_uninit(sc);
		break;
	case USB_HW_POWER_RESUME:
		avr32dci_resume(sc);
		break;
	default:
		break;
	}
}