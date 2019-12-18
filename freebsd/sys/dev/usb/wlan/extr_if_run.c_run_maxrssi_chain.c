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
typedef  size_t uint8_t ;
struct run_softc {int nrxchains; } ;
struct rt2860_rxwi {scalar_t__* rssi; } ;

/* Variables and functions */

__attribute__((used)) static __inline uint8_t
run_maxrssi_chain(struct run_softc *sc, const struct rt2860_rxwi *rxwi)
{
	uint8_t rxchain = 0;

	if (sc->nrxchains > 1) {
		if (rxwi->rssi[1] > rxwi->rssi[rxchain])
			rxchain = 1;
		if (sc->nrxchains > 2)
			if (rxwi->rssi[2] > rxwi->rssi[rxchain])
				rxchain = 2;
	}
	return (rxchain);
}