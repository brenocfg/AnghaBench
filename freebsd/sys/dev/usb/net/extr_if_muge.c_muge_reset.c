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
typedef  scalar_t__ usb_error_t ;
struct usb_config_descriptor {int /*<<< orphan*/  bConfigurationValue; } ;
struct TYPE_2__ {int /*<<< orphan*/  ue_udev; } ;
struct muge_softc {TYPE_1__ sc_ue; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int hz ; 
 int /*<<< orphan*/  lan78xx_chip_init (struct muge_softc*) ; 
 int /*<<< orphan*/  muge_warn_printf (struct muge_softc*,char*) ; 
 int /*<<< orphan*/  uether_pause (TYPE_1__*,int) ; 
 struct usb_config_descriptor* usbd_get_config_descriptor (int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_req_set_config (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
muge_reset(struct muge_softc *sc)
{
	struct usb_config_descriptor *cd;
	usb_error_t err;

	cd = usbd_get_config_descriptor(sc->sc_ue.ue_udev);

	err = usbd_req_set_config(sc->sc_ue.ue_udev, &sc->sc_mtx,
	    cd->bConfigurationValue);
	if (err)
		muge_warn_printf(sc, "reset failed (ignored)\n");

	/* Wait a little while for the chip to get its brains in order. */
	uether_pause(&sc->sc_ue, hz / 100);

	/* Reinitialize controller to achieve full reset. */
	lan78xx_chip_init(sc);
}