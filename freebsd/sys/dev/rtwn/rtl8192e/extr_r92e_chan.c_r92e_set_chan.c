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
typedef  int /*<<< orphan*/  u_int ;
struct rtwn_softc {int nrxchains; struct r92e_softc* sc_priv; } ;
struct r92e_softc {int /*<<< orphan*/ * rf_chnlbw; } ;
struct ieee80211_channel {int dummy; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_HT40 (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  IEEE80211_IS_CHAN_HT40U (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW ; 
 int /*<<< orphan*/  R92C_RF_CHNLBW_CHNL ; 
 int /*<<< orphan*/  RW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r92e_set_bw20 (struct rtwn_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r92e_set_bw40 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r92e_set_txpower (struct rtwn_softc*,struct ieee80211_channel*) ; 
 int /*<<< orphan*/  rtwn_chan2centieee (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  rtwn_rf_write (struct rtwn_softc*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
r92e_set_chan(struct rtwn_softc *sc, struct ieee80211_channel *c)
{
	struct r92e_softc *rs = sc->sc_priv;
	u_int chan;
	int i;

	chan = rtwn_chan2centieee(c);

	for (i = 0; i < sc->nrxchains; i++) {
		rtwn_rf_write(sc, i, R92C_RF_CHNLBW,
		    RW(rs->rf_chnlbw[0], R92C_RF_CHNLBW_CHNL, chan));
	}

	if (IEEE80211_IS_CHAN_HT40(c))
		r92e_set_bw40(sc, chan, IEEE80211_IS_CHAN_HT40U(c));
	else
		r92e_set_bw20(sc, chan);

	/* Set Tx power for this new channel. */
	r92e_set_txpower(sc, c);
}