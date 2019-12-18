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
struct rtwn_tx_radiotap_header {int /*<<< orphan*/  wt_ihdr; } ;
struct rtwn_rx_radiotap_header {int /*<<< orphan*/  wr_ihdr; } ;
struct rtwn_softc {int /*<<< orphan*/  sc_ic; struct rtwn_tx_radiotap_header sc_txtap; struct rtwn_rx_radiotap_header sc_rxtap; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTWN_RX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  RTWN_TX_RADIOTAP_PRESENT ; 
 int /*<<< orphan*/  ieee80211_radiotap_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rtwn_radiotap_attach(struct rtwn_softc *sc)
{
	struct rtwn_rx_radiotap_header *rxtap = &sc->sc_rxtap;
	struct rtwn_tx_radiotap_header *txtap = &sc->sc_txtap;

	ieee80211_radiotap_attach(&sc->sc_ic,
	    &txtap->wt_ihdr, sizeof(*txtap), RTWN_TX_RADIOTAP_PRESENT,
	    &rxtap->wr_ihdr, sizeof(*rxtap), RTWN_RX_RADIOTAP_PRESENT);
}