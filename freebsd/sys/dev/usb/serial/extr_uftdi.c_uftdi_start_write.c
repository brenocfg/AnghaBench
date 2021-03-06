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
struct uftdi_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ucom_softc {struct uftdi_softc* sc_parent; } ;

/* Variables and functions */
 size_t UFTDI_BULK_DT_WR ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uftdi_start_write(struct ucom_softc *ucom)
{
	struct uftdi_softc *sc = ucom->sc_parent;

	usbd_transfer_start(sc->sc_xfer[UFTDI_BULK_DT_WR]);
}