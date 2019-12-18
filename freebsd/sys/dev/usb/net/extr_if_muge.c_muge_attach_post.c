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
struct usb_ether {int dummy; } ;
struct muge_softc {int sc_phyno; } ;

/* Variables and functions */
 int /*<<< orphan*/  lan78xx_chip_init (struct muge_softc*) ; 
 int /*<<< orphan*/  muge_dbg_printf (struct muge_softc*,char*) ; 
 int /*<<< orphan*/  muge_set_leds (struct usb_ether*) ; 
 int /*<<< orphan*/  muge_set_mac_addr (struct usb_ether*) ; 
 struct muge_softc* uether_getsc (struct usb_ether*) ; 

__attribute__((used)) static void
muge_attach_post(struct usb_ether *ue)
{
	struct muge_softc *sc = uether_getsc(ue);

	muge_dbg_printf(sc, "Calling muge_attach_post.\n");

	/* Setup some of the basics */
	sc->sc_phyno = 1;

	muge_set_mac_addr(ue);
	muge_set_leds(ue);

	/* Initialise the chip for the first time */
	lan78xx_chip_init(sc);
}