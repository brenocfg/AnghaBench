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
struct bwi_softc {scalar_t__ sc_tx_timer; int /*<<< orphan*/  sc_watchdog_timer; int /*<<< orphan*/  sc_restart_task; int /*<<< orphan*/  sc_tq; TYPE_1__ sc_ic; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWI_ASSERT_LOCKED (struct bwi_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct bwi_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bwi_watchdog(void *arg)
{
	struct bwi_softc *sc;

	sc = arg;
	BWI_ASSERT_LOCKED(sc);
	if (sc->sc_tx_timer != 0 && --sc->sc_tx_timer == 0) {
		device_printf(sc->sc_dev, "watchdog timeout\n");
		counter_u64_add(sc->sc_ic.ic_oerrors, 1);
		taskqueue_enqueue(sc->sc_tq, &sc->sc_restart_task);
	}
	callout_reset(&sc->sc_watchdog_timer, hz, bwi_watchdog, sc);
}