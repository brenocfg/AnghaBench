#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct ieee80211vap {TYPE_1__* iv_txparms; int /*<<< orphan*/  iv_ic; } ;
struct ieee80211_scan_entry {int* se_rates; int* se_xrates; } ;
struct ieee80211_rateset {int rs_nrates; int* rs_rates; } ;
struct ieee80211_channel {int dummy; } ;
struct TYPE_2__ {int ucastrate; } ;

/* Variables and functions */
 int IEEE80211_FIXED_RATE_NONE ; 
 int const IEEE80211_RATE_BASIC ; 
 int IEEE80211_RV (int const) ; 
 size_t ieee80211_chan2mode (struct ieee80211_channel const*) ; 
 struct ieee80211_rateset* ieee80211_get_suprates (int /*<<< orphan*/ ,struct ieee80211_channel const*) ; 

__attribute__((used)) static int
check_rate(struct ieee80211vap *vap, const struct ieee80211_channel *chan,
    const struct ieee80211_scan_entry *se)
{
	const struct ieee80211_rateset *srs;
	int i, j, nrs, r, okrate, badrate, fixedrate, ucastrate;
	const uint8_t *rs;

	okrate = badrate = 0;

	srs = ieee80211_get_suprates(vap->iv_ic, chan);
	nrs = se->se_rates[1];
	rs = se->se_rates+2;
	/* XXX MCS */
	ucastrate = vap->iv_txparms[ieee80211_chan2mode(chan)].ucastrate;
	fixedrate = IEEE80211_FIXED_RATE_NONE;
again:
	for (i = 0; i < nrs; i++) {
		r = IEEE80211_RV(rs[i]);
		badrate = r;
		/*
		 * Check any fixed rate is included. 
		 */
		if (r == ucastrate)
			fixedrate = r;
		/*
		 * Check against our supported rates.
		 */
		for (j = 0; j < srs->rs_nrates; j++)
			if (r == IEEE80211_RV(srs->rs_rates[j])) {
				if (r > okrate)		/* NB: track max */
					okrate = r;
				break;
			}

		if (j == srs->rs_nrates && (rs[i] & IEEE80211_RATE_BASIC)) {
			/*
			 * Don't try joining a BSS, if we don't support
			 * one of its basic rates.
			 */
			okrate = 0;
			goto back;
		}
	}
	if (rs == se->se_rates+2) {
		/* scan xrates too; sort of an algol68-style for loop */
		nrs = se->se_xrates[1];
		rs = se->se_xrates+2;
		goto again;
	}

back:
	if (okrate == 0 || ucastrate != fixedrate)
		return badrate | IEEE80211_RATE_BASIC;
	else
		return IEEE80211_RV(okrate);
}