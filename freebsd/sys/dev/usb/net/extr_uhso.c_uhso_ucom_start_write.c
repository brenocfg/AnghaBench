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
struct uhso_softc {int /*<<< orphan*/ * sc_xfer; int /*<<< orphan*/  sc_type; TYPE_1__* sc_tty; } ;
struct ucom_softc {size_t sc_subunit; struct uhso_softc* sc_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * ht_xfer; } ;

/* Variables and functions */
 size_t UHSO_BULK_ENDPT_WRITE ; 
 size_t UHSO_CTRL_WRITE ; 
 int /*<<< orphan*/  UHSO_DPRINTF (int,char*,size_t) ; 
 int UHSO_IFACE_USB_TYPE (int /*<<< orphan*/ ) ; 
 int UHSO_IF_BULK ; 
 int UHSO_IF_MUX ; 
 size_t UHSO_MUX_ENDPT_INTR ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_xfer_set_priv (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
uhso_ucom_start_write(struct ucom_softc *ucom)
{
	struct uhso_softc *sc = ucom->sc_parent;

	if (UHSO_IFACE_USB_TYPE(sc->sc_type) & UHSO_IF_MUX) {
		UHSO_DPRINTF(3, "local unit %d\n", ucom->sc_subunit);

		usbd_transfer_start(sc->sc_xfer[UHSO_MUX_ENDPT_INTR]);

		usbd_xfer_set_priv(
		    sc->sc_tty[ucom->sc_subunit].ht_xfer[UHSO_CTRL_WRITE],
		    &sc->sc_tty[ucom->sc_subunit]);
		usbd_transfer_start(
		    sc->sc_tty[ucom->sc_subunit].ht_xfer[UHSO_CTRL_WRITE]);

	}
	else if (UHSO_IFACE_USB_TYPE(sc->sc_type) & UHSO_IF_BULK) {
		usbd_transfer_start(sc->sc_xfer[UHSO_BULK_ENDPT_WRITE]);
	}
}