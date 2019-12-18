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
struct umcs7840_softc {int /*<<< orphan*/  sc_intr_xfer; TYPE_1__* sc_ports; } ;
struct ucom_softc {size_t sc_portno; struct umcs7840_softc* sc_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,size_t) ; 
 int UMCS7840_N_TRANSFERS ; 
 int /*<<< orphan*/  usbd_transfer_poll (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
umcs7840_poll(struct ucom_softc *ucom)
{
	struct umcs7840_softc *sc = ucom->sc_parent;

	DPRINTF("Port %d poll\n", ucom->sc_portno);
	usbd_transfer_poll(sc->sc_ports[ucom->sc_portno].sc_xfer, UMCS7840_N_TRANSFERS);
	usbd_transfer_poll(&sc->sc_intr_xfer, 1);
}