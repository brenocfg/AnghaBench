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
typedef  size_t uint8_t ;
struct umcs7840_softc {TYPE_1__* sc_ports; int /*<<< orphan*/  sc_intr_xfer; } ;
struct ucom_softc {size_t sc_portno; struct umcs7840_softc* sc_parent; } ;
struct TYPE_2__ {int /*<<< orphan*/ * sc_xfer; } ;

/* Variables and functions */
 size_t UMCS7840_BULK_RD_EP ; 
 int /*<<< orphan*/  usbd_transfer_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
umcs7840_start_read(struct ucom_softc *ucom)
{
	struct umcs7840_softc *sc = ucom->sc_parent;
	uint8_t pn = ucom->sc_portno;

	/* Start interrupt transfer */
	usbd_transfer_start(sc->sc_intr_xfer);

	/* Start read transfer */
	usbd_transfer_start(sc->sc_ports[pn].sc_xfer[UMCS7840_BULK_RD_EP]);
}