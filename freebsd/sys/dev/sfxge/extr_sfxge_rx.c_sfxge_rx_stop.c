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
struct sfxge_softc {int rxq_count; int /*<<< orphan*/  enp; scalar_t__ rx_buffer_size; scalar_t__ rx_prefix_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  efx_mac_filter_default_rxq_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_rx_fini (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfxge_rx_qstop (struct sfxge_softc*,int) ; 

void
sfxge_rx_stop(struct sfxge_softc *sc)
{
	int index;

	efx_mac_filter_default_rxq_clear(sc->enp);

	/* Stop the receive queue(s) */
	index = sc->rxq_count;
	while (--index >= 0)
		sfxge_rx_qstop(sc, index);

	sc->rx_prefix_size = 0;
	sc->rx_buffer_size = 0;

	efx_rx_fini(sc->enp);
}