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
typedef  size_t uint8_t ;
struct usb_hw_ep_profile {int dummy; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct dwc_otg_softc {size_t sc_dev_ep_max; TYPE_1__* sc_hw_ep_profile; } ;
struct TYPE_2__ {struct usb_hw_ep_profile usb; } ;

/* Variables and functions */
 struct dwc_otg_softc* DWC_OTG_BUS2SC (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dwc_otg_get_hw_ep_profile(struct usb_device *udev,
    const struct usb_hw_ep_profile **ppf, uint8_t ep_addr)
{
	struct dwc_otg_softc *sc;

	sc = DWC_OTG_BUS2SC(udev->bus);

	if (ep_addr < sc->sc_dev_ep_max)
		*ppf = &sc->sc_hw_ep_profile[ep_addr].usb;
	else
		*ppf = NULL;
}