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
struct rtwn_softc {int /*<<< orphan*/  sc_ht40; } ;
struct r88e_rx_phystat {int /*<<< orphan*/  chan; } ;
struct ieee80211_rx_stats {int r_flags; int /*<<< orphan*/  c_ieee; int /*<<< orphan*/  c_freq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_CHAN_2GHZ ; 
 int IEEE80211_R_FREQ ; 
 int IEEE80211_R_IEEE ; 
 int /*<<< orphan*/  ieee80211_ieee2mhz (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r92c_get_rx_stats (struct rtwn_softc*,struct ieee80211_rx_stats*,void const*,void const*) ; 

void
r88e_get_rx_stats(struct rtwn_softc *sc, struct ieee80211_rx_stats *rxs,
    const void *desc, const void *physt_ptr)
{
	const struct r88e_rx_phystat *physt = physt_ptr;

	r92c_get_rx_stats(sc, rxs, desc, physt_ptr);

	if (!sc->sc_ht40) {	/* XXX center channel */
		rxs->r_flags |= IEEE80211_R_IEEE | IEEE80211_R_FREQ;
		rxs->c_ieee = physt->chan;
		rxs->c_freq = ieee80211_ieee2mhz(rxs->c_ieee,
		    IEEE80211_CHAN_2GHZ);
	}
}