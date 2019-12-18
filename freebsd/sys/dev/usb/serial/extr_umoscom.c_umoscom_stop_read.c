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
struct umoscom_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ucom_softc {struct umoscom_softc* sc_parent; } ;

/* Variables and functions */
 size_t UMOSCOM_BULK_DT_RD ; 
 size_t UMOSCOM_INTR_DT_RD ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umoscom_stop_read(struct ucom_softc *ucom)
{
	struct umoscom_softc *sc = ucom->sc_parent;

	/* stop interrupt transfer */
	usbd_transfer_stop(sc->sc_xfer[UMOSCOM_INTR_DT_RD]);

	/* stop read endpoint */
	usbd_transfer_stop(sc->sc_xfer[UMOSCOM_BULK_DT_RD]);
}