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
struct uss820dci_softc {int dummy; } ;
struct usb_bus {int dummy; } ;

/* Variables and functions */
#define  USB_HW_POWER_RESUME 130 
#define  USB_HW_POWER_SHUTDOWN 129 
#define  USB_HW_POWER_SUSPEND 128 
 struct uss820dci_softc* USS820_DCI_BUS2SC (struct usb_bus*) ; 
 int /*<<< orphan*/  uss820dci_resume (struct uss820dci_softc*) ; 
 int /*<<< orphan*/  uss820dci_suspend (struct uss820dci_softc*) ; 
 int /*<<< orphan*/  uss820dci_uninit (struct uss820dci_softc*) ; 

__attribute__((used)) static void
uss820dci_set_hw_power_sleep(struct usb_bus *bus, uint32_t state)
{
	struct uss820dci_softc *sc = USS820_DCI_BUS2SC(bus);

	switch (state) {
	case USB_HW_POWER_SUSPEND:
		uss820dci_suspend(sc);
		break;
	case USB_HW_POWER_SHUTDOWN:
		uss820dci_uninit(sc);
		break;
	case USB_HW_POWER_RESUME:
		uss820dci_resume(sc);
		break;
	default:
		break;
	}
}