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
struct TYPE_2__ {int /*<<< orphan*/  ic_macaddr; } ;
struct wi_softc {int sc_enabled; int /*<<< orphan*/  sc_watchdog; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  sc_dev; TYPE_1__ sc_ic; int /*<<< orphan*/  sc_porttype; } ;

/* Variables and functions */
 int /*<<< orphan*/  WI_FLAGS_RUNNING ; 
 int /*<<< orphan*/  WI_LOCK_ASSERT (struct wi_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wi_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  wi_enable (struct wi_softc*) ; 
 scalar_t__ wi_setup_locked (struct wi_softc*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_stop (struct wi_softc*,int) ; 
 int /*<<< orphan*/  wi_watchdog ; 

void
wi_init(struct wi_softc *sc)
{
	int wasenabled;

	WI_LOCK_ASSERT(sc);

	wasenabled = sc->sc_enabled;
	if (wasenabled)
		wi_stop(sc, 1);

	if (wi_setup_locked(sc, sc->sc_porttype, 3,
	    sc->sc_ic.ic_macaddr) != 0) {
		device_printf(sc->sc_dev, "interface not running\n");
		wi_stop(sc, 1);
		return;
	}

	sc->sc_flags |= WI_FLAGS_RUNNING;

	callout_reset(&sc->sc_watchdog, hz, wi_watchdog, sc);

	wi_enable(sc);			/* Enable desired port */
}