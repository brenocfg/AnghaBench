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
struct ieee80211com {int ic_flags; int /*<<< orphan*/  ic_rt; } ;
struct rtwn_softc {struct ieee80211com sc_ic; } ;
struct r12a_tx_desc {int /*<<< orphan*/  txdw5; int /*<<< orphan*/  txdw4; int /*<<< orphan*/  txdw3; } ;
typedef  enum ieee80211_protmode { ____Placeholder_ieee80211_protmode } ieee80211_protmode ;

/* Variables and functions */
 int IEEE80211_F_SHPREAMBLE ; 
#define  IEEE80211_PROT_CTSONLY 129 
#define  IEEE80211_PROT_RTSCTS 128 
 int /*<<< orphan*/  IEEE80211_RV (size_t) ; 
 int /*<<< orphan*/  R12A_TXDW3_CTS2SELF ; 
 int /*<<< orphan*/  R12A_TXDW3_RTSEN ; 
 int /*<<< orphan*/  R12A_TXDW4_RTSRATE ; 
 int /*<<< orphan*/  R12A_TXDW4_RTSRATE_FB_LMT ; 
 int /*<<< orphan*/  R12A_TXDW5_RTS_SHORT ; 
 scalar_t__ RTWN_RATE_IS_CCK (size_t) ; 
 size_t RTWN_RIDX_CCK1 ; 
 size_t RTWN_RIDX_HT_MCS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 
 size_t ieee80211_ctl_rate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t rate2ridx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ridx2rate ; 
 size_t rtwn_ctl_mcsrate (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void
r12a_tx_protection(struct rtwn_softc *sc, struct r12a_tx_desc *txd,
    enum ieee80211_protmode mode, uint8_t ridx)
{
	struct ieee80211com *ic = &sc->sc_ic;
	uint8_t rate;

	switch (mode) {
	case IEEE80211_PROT_CTSONLY:
		txd->txdw3 |= htole32(R12A_TXDW3_CTS2SELF);
		break;
	case IEEE80211_PROT_RTSCTS:
		txd->txdw3 |= htole32(R12A_TXDW3_RTSEN);
		break;
	default:
		break;
	}

	if (mode == IEEE80211_PROT_CTSONLY ||
	    mode == IEEE80211_PROT_RTSCTS) {
		if (ridx >= RTWN_RIDX_HT_MCS(0))
			rate = rtwn_ctl_mcsrate(ic->ic_rt, ridx);
		else
			rate = ieee80211_ctl_rate(ic->ic_rt, ridx2rate[ridx]);
		ridx = rate2ridx(IEEE80211_RV(rate));

		txd->txdw4 |= htole32(SM(R12A_TXDW4_RTSRATE, ridx));
		/* RTS rate fallback limit (max). */
		txd->txdw4 |= htole32(SM(R12A_TXDW4_RTSRATE_FB_LMT, 0xf));

		if (RTWN_RATE_IS_CCK(ridx) && ridx != RTWN_RIDX_CCK1 &&
		    (ic->ic_flags & IEEE80211_F_SHPREAMBLE))
			txd->txdw5 |= htole32(R12A_TXDW5_RTS_SHORT);
	}
}