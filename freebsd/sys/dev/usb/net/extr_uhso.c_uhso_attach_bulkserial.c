#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
struct usb_interface {TYPE_1__* idesc; } ;
struct uhso_softc {TYPE_2__* sc_tty; int /*<<< orphan*/  sc_xfer; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_udev; } ;
struct TYPE_4__ {int ht_muxport; } ;
struct TYPE_3__ {int /*<<< orphan*/  bInterfaceNumber; } ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ UHSO_BULK_ENDPT_MAX ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int /*<<< orphan*/ ,char*) ; 
 int uhso_alloc_tty (struct uhso_softc*) ; 
 int /*<<< orphan*/  uhso_bs_config ; 
 scalar_t__ usbd_transfer_setup (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct uhso_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
uhso_attach_bulkserial(struct uhso_softc *sc, struct usb_interface *iface,
    int type)
{
	usb_error_t uerr;
	int tty;

	/* Try attaching RD/WR/INTR first */
	uerr = usbd_transfer_setup(sc->sc_udev,
	    &iface->idesc->bInterfaceNumber, sc->sc_xfer,
	    uhso_bs_config, UHSO_BULK_ENDPT_MAX, sc, &sc->sc_mtx);
	if (uerr) {
		/* Try only RD/WR */
		uerr = usbd_transfer_setup(sc->sc_udev,
		    &iface->idesc->bInterfaceNumber, sc->sc_xfer,
		    uhso_bs_config, UHSO_BULK_ENDPT_MAX - 1, sc, &sc->sc_mtx);
	}
	if (uerr) {
		UHSO_DPRINTF(0, "usbd_transfer_setup failed");
		return (-1);
	}

	tty = uhso_alloc_tty(sc);
	if (tty < 0) {
		usbd_transfer_unsetup(sc->sc_xfer, UHSO_BULK_ENDPT_MAX);
		return (ENOMEM);
	}

	sc->sc_tty[tty].ht_muxport = -1;
	return (0);
}