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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211com {int ic_curmode; struct ieee80211_channel* ic_curchan; } ;
struct rtwn_softc {int /*<<< orphan*/  sc_dev; struct ieee80211com sc_ic; } ;
struct r92c_tx_desc {int /*<<< orphan*/  txdw1; } ;
struct ieee80211vap {int iv_flags; int iv_flags_ht; } ;
struct ieee80211_node {int ni_flags; struct ieee80211_channel* ni_chan; struct ieee80211vap* ni_vap; } ;
struct ieee80211_channel {int dummy; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 struct ieee80211_channel* IEEE80211_CHAN_ANYC ; 
 int IEEE80211_FHT_PUREN ; 
 int IEEE80211_F_PUREG ; 
#define  IEEE80211_MODE_11B 130 
#define  IEEE80211_MODE_11G 129 
#define  IEEE80211_MODE_11NG 128 
 int IEEE80211_NODE_HT ; 
 int /*<<< orphan*/  R92C_RAID_11B ; 
 int /*<<< orphan*/  R92C_RAID_11BG ; 
 int /*<<< orphan*/  R92C_RAID_11BGN ; 
 int /*<<< orphan*/  R92C_RAID_11G ; 
 int /*<<< orphan*/  R92C_RAID_11N ; 
 int /*<<< orphan*/  R92C_TXDW1_RAID ; 
 int /*<<< orphan*/  SM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 int ieee80211_chan2mode (struct ieee80211_channel*) ; 

__attribute__((used)) static void
r92c_tx_raid(struct rtwn_softc *sc, struct r92c_tx_desc *txd,
    struct ieee80211_node *ni, int ismcast)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_channel *chan;
	enum ieee80211_phymode mode;
	uint8_t raid;

	chan = (ni->ni_chan != IEEE80211_CHAN_ANYC) ?
		ni->ni_chan : ic->ic_curchan;
	mode = ieee80211_chan2mode(chan);

	/* NB: group addressed frames are done at 11bg rates for now */
	if (ismcast || !(ni->ni_flags & IEEE80211_NODE_HT)) {
		switch (mode) {
		case IEEE80211_MODE_11B:
		case IEEE80211_MODE_11G:
			break;
		case IEEE80211_MODE_11NG:
			mode = IEEE80211_MODE_11G;
			break;
		default:
			device_printf(sc->sc_dev, "unknown mode(1) %d!\n",
			    ic->ic_curmode);
			return;
		}
	}

	switch (mode) {
	case IEEE80211_MODE_11B:
		raid = R92C_RAID_11B;
		break;
	case IEEE80211_MODE_11G:
		if (vap->iv_flags & IEEE80211_F_PUREG)
			raid = R92C_RAID_11G;
		else
			raid = R92C_RAID_11BG;
		break;
	case IEEE80211_MODE_11NG:
		if (vap->iv_flags_ht & IEEE80211_FHT_PUREN)
			raid = R92C_RAID_11N;
		else
			raid = R92C_RAID_11BGN;
		break;
	default:
		device_printf(sc->sc_dev, "unknown mode(2) %d!\n", mode);
		return;
	}

	txd->txdw1 |= htole32(SM(R92C_TXDW1_RAID, raid));
}