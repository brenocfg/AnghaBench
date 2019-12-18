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
typedef  int uint8_t ;
struct wmeParams {int wmep_aifsn; int wmep_txopLimit; int wmep_logcwmin; int wmep_logcwmax; int wmep_acm; } ;
struct rtwn_softc {struct wmeParams* cap_wmeParams; } ;
struct ieee80211com {struct rtwn_softc* ic_softc; struct ieee80211_channel* ic_curchan; } ;
struct ieee80211_channel {int dummy; } ;
struct chanAccParams {int /*<<< orphan*/  cap_wmeParams; } ;

/* Variables and functions */
 int IEEE80211_DUR_OFDM_SIFS ; 
 int IEEE80211_DUR_SIFS ; 
 int IEEE80211_GET_SLOTTIME (struct ieee80211com*) ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (struct ieee80211_channel*) ; 
 int /*<<< orphan*/  IEEE80211_LOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  IEEE80211_UNLOCK (struct ieee80211com*) ; 
 int /*<<< orphan*/  R92C_ACMHWCTRL ; 
 int /*<<< orphan*/  R92C_ACMHWCTRL_ACM_MASK ; 
 int R92C_ACMHWCTRL_EN ; 
 int /*<<< orphan*/  R92C_EDCA_PARAM_AIFS ; 
 int /*<<< orphan*/  R92C_EDCA_PARAM_ECWMAX ; 
 int /*<<< orphan*/  R92C_EDCA_PARAM_ECWMIN ; 
 int /*<<< orphan*/  R92C_EDCA_PARAM_TXOP ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 int SM (int /*<<< orphan*/ ,int) ; 
 int WME_AC_BE ; 
 int WME_NUM_AC ; 
 int /*<<< orphan*/  ieee80211_wme_ic_getparams (struct ieee80211com*,struct chanAccParams*) ; 
 int /*<<< orphan*/  memcpy (struct wmeParams*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_setbits_1 (struct rtwn_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtwn_write_4 (struct rtwn_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * wme2reg ; 

__attribute__((used)) static int
rtwn_wme_update(struct ieee80211com *ic)
{
	struct chanAccParams chp;
	struct ieee80211_channel *c = ic->ic_curchan;
	struct rtwn_softc *sc = ic->ic_softc;
	struct wmeParams *wmep = sc->cap_wmeParams;
	uint8_t aifs, acm, slottime;
	int ac;

	ieee80211_wme_ic_getparams(ic, &chp);

	/* Prevent possible races. */
	IEEE80211_LOCK(ic);	/* XXX */
	RTWN_LOCK(sc);
	memcpy(wmep, chp.cap_wmeParams, sizeof(sc->cap_wmeParams));
	RTWN_UNLOCK(sc);
	IEEE80211_UNLOCK(ic);

	acm = 0;
	slottime = IEEE80211_GET_SLOTTIME(ic);

	RTWN_LOCK(sc);
	for (ac = WME_AC_BE; ac < WME_NUM_AC; ac++) {
		/* AIFS[AC] = AIFSN[AC] * aSlotTime + aSIFSTime. */
		aifs = wmep[ac].wmep_aifsn * slottime +
		    (IEEE80211_IS_CHAN_5GHZ(c) ?
			IEEE80211_DUR_OFDM_SIFS : IEEE80211_DUR_SIFS);
		rtwn_write_4(sc, wme2reg[ac],
		    SM(R92C_EDCA_PARAM_TXOP, wmep[ac].wmep_txopLimit) |
		    SM(R92C_EDCA_PARAM_ECWMIN, wmep[ac].wmep_logcwmin) |
		    SM(R92C_EDCA_PARAM_ECWMAX, wmep[ac].wmep_logcwmax) |
		    SM(R92C_EDCA_PARAM_AIFS, aifs));
		if (ac != WME_AC_BE)
			acm |= wmep[ac].wmep_acm << ac;
	}

	if (acm != 0)
		acm |= R92C_ACMHWCTRL_EN;
	rtwn_setbits_1(sc, R92C_ACMHWCTRL, R92C_ACMHWCTRL_ACM_MASK, acm);
	RTWN_UNLOCK(sc);

	return 0;
}