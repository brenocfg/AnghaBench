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
struct ucom_softc {struct ubser_softc* sc_parent; } ;
struct ubser_softc {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t UBSER_BULK_DT_RD ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ubser_stop_read(struct ucom_softc *ucom)
{
	struct ubser_softc *sc = ucom->sc_parent;

	usbd_transfer_stop(sc->sc_xfer[UBSER_BULK_DT_RD]);
}