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
struct glc_softc {size_t sc_next_rxdma_slot; scalar_t__ sc_wdog_timer; int /*<<< orphan*/  sc_self; int /*<<< orphan*/  sc_tick_ch; TYPE_1__* sc_rxsoft; int /*<<< orphan*/  sc_dev; int /*<<< orphan*/  sc_bus; int /*<<< orphan*/  sc_mtx; } ;
struct TYPE_2__ {int /*<<< orphan*/  rxs_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (void*),struct glc_softc*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glc_init_locked (struct glc_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  lv1_net_start_rx_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
glc_tick(void *xsc)
{
	struct glc_softc *sc = xsc;

	mtx_assert(&sc->sc_mtx, MA_OWNED);

	/*
	 * XXX: Sometimes the RX queue gets stuck. Poke it periodically until
	 * we figure out why. This will fail harmlessly if the RX queue is
	 * already running.
	 */
	lv1_net_start_rx_dma(sc->sc_bus, sc->sc_dev,
	    sc->sc_rxsoft[sc->sc_next_rxdma_slot].rxs_desc, 0);

	if (sc->sc_wdog_timer == 0 || --sc->sc_wdog_timer != 0) {
		callout_reset(&sc->sc_tick_ch, hz, glc_tick, sc);
		return;
	}

	/* Problems */
	device_printf(sc->sc_self, "device timeout\n");

	glc_init_locked(sc);
}