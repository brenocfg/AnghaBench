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
struct uvscom_softc {int /*<<< orphan*/ * sc_xfer; } ;
struct ucom_softc {struct uvscom_softc* sc_parent; } ;

/* Variables and functions */
 size_t UVSCOM_BULK_DT_WR ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
uvscom_stop_write(struct ucom_softc *ucom)
{
	struct uvscom_softc *sc = ucom->sc_parent;

	usbd_transfer_stop(sc->sc_xfer[UVSCOM_BULK_DT_WR]);
}