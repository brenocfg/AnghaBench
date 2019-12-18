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
struct usie_softc {int /*<<< orphan*/ ** sc_uc_xfer; } ;
struct ucom_softc {size_t sc_subunit; struct usie_softc* sc_parent; } ;

/* Variables and functions */
 size_t USIE_UC_TX ; 
 int /*<<< orphan*/  usbd_transfer_stop (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usie_uc_stop_write(struct ucom_softc *ucom)
{
	struct usie_softc *sc = ucom->sc_parent;

	usbd_transfer_stop(sc->sc_uc_xfer[ucom->sc_subunit][USIE_UC_TX]);
}