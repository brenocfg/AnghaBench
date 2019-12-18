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
typedef  scalar_t__ uint8_t ;
struct usb_hw_ep_profile {int dummy; } ;
struct usb_device {int /*<<< orphan*/  bus; } ;
struct musbotg_softc {scalar_t__ sc_ep_max; struct usb_hw_ep_profile* sc_hw_ep_profile; } ;

/* Variables and functions */
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 
 struct usb_hw_ep_profile* musbotg_ep_profile ; 

__attribute__((used)) static void
musbotg_get_hw_ep_profile(struct usb_device *udev,
    const struct usb_hw_ep_profile **ppf, uint8_t ep_addr)
{
	struct musbotg_softc *sc;

	sc = MUSBOTG_BUS2SC(udev->bus);

	if (ep_addr == 0) {
		/* control endpoint */
		*ppf = musbotg_ep_profile;
	} else if (ep_addr <= sc->sc_ep_max) {
		/* other endpoints */
		*ppf = sc->sc_hw_ep_profile + ep_addr;
	} else {
		*ppf = NULL;
	}
}