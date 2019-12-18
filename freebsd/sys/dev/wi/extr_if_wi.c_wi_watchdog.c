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
struct wi_softc {scalar_t__ sc_tx_timer; int /*<<< orphan*/  sc_watchdog; TYPE_1__ sc_ic; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  WI_LOCK_ASSERT (struct wi_softc*) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct wi_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  wi_init (struct wi_softc*) ; 

__attribute__((used)) static void
wi_watchdog(void *arg)
{
	struct wi_softc	*sc = arg;

	WI_LOCK_ASSERT(sc);

	if (!sc->sc_enabled)
		return;

	if (sc->sc_tx_timer && --sc->sc_tx_timer == 0) {
		device_printf(sc->sc_dev, "device timeout\n");
		counter_u64_add(sc->sc_ic.ic_oerrors, 1);
		wi_init(sc);
		return;
	}
	callout_reset(&sc->sc_watchdog, hz, wi_watchdog, sc);
}