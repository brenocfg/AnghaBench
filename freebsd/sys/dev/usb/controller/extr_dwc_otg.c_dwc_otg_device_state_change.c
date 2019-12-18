#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {scalar_t__ state; int /*<<< orphan*/  bus; TYPE_1__ flags; } ;
struct dwc_otg_softc {int sc_dev_ep_max; int sc_dev_in_ep_max; int /*<<< orphan*/  sc_bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIEPCTL_EPDIS ; 
 int /*<<< orphan*/  DOEPCTL_EPDIS ; 
 int /*<<< orphan*/  DOTG_DIEPCTL (int) ; 
 int /*<<< orphan*/  DOTG_DOEPCTL (int) ; 
 struct dwc_otg_softc* DWC_OTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DWC_OTG_WRITE_4 (struct dwc_otg_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 scalar_t__ USB_STATE_ADDRESSED ; 
 scalar_t__ USB_STATE_CONFIGURED ; 

__attribute__((used)) static void
dwc_otg_device_state_change(struct usb_device *udev)
{
	struct dwc_otg_softc *sc;
	uint8_t x;

	/* check mode */
	if (udev->flags.usb_mode != USB_MODE_DEVICE) {
		/* not supported */
		return;
	}

	/* get softc */
	sc = DWC_OTG_BUS2SC(udev->bus);

	/* deactivate all other endpoint but the control endpoint */
	if (udev->state == USB_STATE_CONFIGURED ||
	    udev->state == USB_STATE_ADDRESSED) {

		USB_BUS_LOCK(&sc->sc_bus);

		for (x = 1; x != sc->sc_dev_ep_max; x++) {

			if (x < sc->sc_dev_in_ep_max) {
				DWC_OTG_WRITE_4(sc, DOTG_DIEPCTL(x),
				    DIEPCTL_EPDIS);
				DWC_OTG_WRITE_4(sc, DOTG_DIEPCTL(x), 0);
			}

			DWC_OTG_WRITE_4(sc, DOTG_DOEPCTL(x),
			    DOEPCTL_EPDIS);
			DWC_OTG_WRITE_4(sc, DOTG_DOEPCTL(x), 0);
		}
		USB_BUS_UNLOCK(&sc->sc_bus);
	}
}