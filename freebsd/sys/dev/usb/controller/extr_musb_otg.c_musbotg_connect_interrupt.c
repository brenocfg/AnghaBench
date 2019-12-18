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
struct TYPE_2__ {int change_connect; } ;
struct musbotg_softc {int /*<<< orphan*/  sc_bus; TYPE_1__ sc_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  musbotg_root_intr (struct musbotg_softc*) ; 

void
musbotg_connect_interrupt(struct musbotg_softc *sc)
{
	USB_BUS_LOCK(&sc->sc_bus);
	sc->sc_flags.change_connect = 1;

	/* complete root HUB interrupt endpoint */
	musbotg_root_intr(sc);
	USB_BUS_UNLOCK(&sc->sc_bus);
}