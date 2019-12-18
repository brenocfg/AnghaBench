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
struct atmegadci_softc {int dummy; } ;

/* Variables and functions */
 struct atmegadci_softc* ATMEGA_BUS2SC (struct usb_bus*) ; 
#define  USB_HW_POWER_RESUME 130 
#define  USB_HW_POWER_SHUTDOWN 129 
#define  USB_HW_POWER_SUSPEND 128 
 int /*<<< orphan*/  atmegadci_resume (struct atmegadci_softc*) ; 
 int /*<<< orphan*/  atmegadci_suspend (struct atmegadci_softc*) ; 
 int /*<<< orphan*/  atmegadci_uninit (struct atmegadci_softc*) ; 

__attribute__((used)) static void
atmegadci_set_hw_power_sleep(struct usb_bus *bus, uint32_t state)
{
	struct atmegadci_softc *sc = ATMEGA_BUS2SC(bus);

	switch (state) {
	case USB_HW_POWER_SUSPEND:
		atmegadci_suspend(sc);
		break;
	case USB_HW_POWER_SHUTDOWN:
		atmegadci_uninit(sc);
		break;
	case USB_HW_POWER_RESUME:
		atmegadci_resume(sc);
		break;
	default:
		break;
	}
}