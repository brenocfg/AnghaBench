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
struct ufoma_softc {int /*<<< orphan*/ * sc_bulk_xfer; int /*<<< orphan*/ * sc_ctrl_xfer; scalar_t__ sc_nobulk; } ;
struct ucom_softc {struct ufoma_softc* sc_parent; } ;

/* Variables and functions */
 size_t UFOMA_BULK_ENDPT_WRITE ; 
 size_t UFOMA_CTRL_ENDPT_WRITE ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ufoma_start_write(struct ucom_softc *ucom)
{
	struct ufoma_softc *sc = ucom->sc_parent;

	if (sc->sc_nobulk) {
		usbd_transfer_start(sc->sc_ctrl_xfer[UFOMA_CTRL_ENDPT_WRITE]);
	} else {
		usbd_transfer_start(sc->sc_bulk_xfer[UFOMA_BULK_ENDPT_WRITE]);
	}
}