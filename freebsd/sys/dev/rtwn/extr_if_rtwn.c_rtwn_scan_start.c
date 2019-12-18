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
struct rtwn_softc {scalar_t__ bcn_vaps; } ;
struct ieee80211com {struct rtwn_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  R92C_TXPAUSE ; 
 int /*<<< orphan*/  R92C_TX_QUEUE_BCN ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  rtwn_set_rx_bssid_all (struct rtwn_softc*,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_scan_start(struct ieee80211com *ic)
{
	struct rtwn_softc *sc = ic->ic_softc;

	RTWN_LOCK(sc);
	/* Pause beaconing. */
	rtwn_setbits_1(sc, R92C_TXPAUSE, 0, R92C_TX_QUEUE_BCN);
	/* Receive beacons / probe responses from any BSSID. */
	if (sc->bcn_vaps == 0)
		rtwn_set_rx_bssid_all(sc, 1);
	RTWN_UNLOCK(sc);
}