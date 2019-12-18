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
struct hn_softc {int /*<<< orphan*/  hn_rx_filter; } ;

/* Variables and functions */
 int /*<<< orphan*/  NDIS_PACKET_TYPE_NONE ; 
 int /*<<< orphan*/  hn_rndis_set_rxfilter (struct hn_softc*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  pause (char*,int) ; 

__attribute__((used)) static void
hn_disable_rx(struct hn_softc *sc)
{

	/*
	 * Disable RX by clearing RX filter forcefully.
	 */
	sc->hn_rx_filter = NDIS_PACKET_TYPE_NONE;
	hn_rndis_set_rxfilter(sc, sc->hn_rx_filter); /* ignore error */

	/*
	 * Give RNDIS enough time to flush all pending data packets.
	 */
	pause("waitrx", (200 * hz) / 1000);
}