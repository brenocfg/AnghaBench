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
struct TYPE_2__ {int /*<<< orphan*/  ic_oerrors; } ;
struct rt2860_softc {int sc_flags; scalar_t__ sc_tx_timer; int /*<<< orphan*/  watchdog_ch; TYPE_1__ sc_ic; int /*<<< orphan*/  sc_dev; scalar_t__ sc_invalid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2860_softc*) ; 
 int RT2860_RUNNING ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct rt2860_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  rt2860_init_locked (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_stop_locked (struct rt2860_softc*) ; 

__attribute__((used)) static void
rt2860_watchdog(void *arg)
{
	struct rt2860_softc *sc = arg;

	RAL_LOCK_ASSERT(sc);

	KASSERT(sc->sc_flags & RT2860_RUNNING, ("not running"));

	if (sc->sc_invalid)		/* card ejected */
		return;

	if (sc->sc_tx_timer > 0 && --sc->sc_tx_timer == 0) {
		device_printf(sc->sc_dev, "device timeout\n");
		rt2860_stop_locked(sc);
		rt2860_init_locked(sc);
		counter_u64_add(sc->sc_ic.ic_oerrors, 1);
		return;
	}
	callout_reset(&sc->watchdog_ch, hz, rt2860_watchdog, sc);
}