#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mst_watchdog; } ;
struct TYPE_3__ {int /*<<< orphan*/  ic_oerrors; } ;
struct mwl_softc {scalar_t__ sc_tx_timer; TYPE_2__ sc_stats; TYPE_1__ sc_ic; int /*<<< orphan*/ * sc_txq; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_mh; int /*<<< orphan*/  sc_invalid; scalar_t__ sc_running; int /*<<< orphan*/  sc_watchdog; } ;

/* Variables and functions */
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct mwl_softc*) ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  hz ; 
 scalar_t__ mwl_hal_setkeepalive (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_reset (struct mwl_softc*) ; 
 int /*<<< orphan*/  mwl_txq_dump (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mwl_watchdog(void *arg)
{
	struct mwl_softc *sc = arg;

	callout_reset(&sc->sc_watchdog, hz, mwl_watchdog, sc);
	if (sc->sc_tx_timer == 0 || --sc->sc_tx_timer > 0)
		return;

	if (sc->sc_running && !sc->sc_invalid) {
		if (mwl_hal_setkeepalive(sc->sc_mh))
			device_printf(sc->sc_dev,
			    "transmit timeout (firmware hung?)\n");
		else
			device_printf(sc->sc_dev,
			    "transmit timeout\n");
#if 0
		mwl_reset(sc);
mwl_txq_dump(&sc->sc_txq[0]);/*XXX*/
#endif
		counter_u64_add(sc->sc_ic.ic_oerrors, 1);
		sc->sc_stats.mst_watchdog++;
	}
}