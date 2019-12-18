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
struct ieee80211_rateset {int* rs_rates; int rs_nrates; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_vap; struct ieee80211_rateset ni_rates; int /*<<< orphan*/  ni_htrates; } ;
struct ieee80211_amrr_node {int amn_rix; int amn_success; int amn_success_threshold; int amn_recovery; scalar_t__ amn_retrycnt; scalar_t__ amn_txcnt; } ;
struct ieee80211_amrr {int amrr_max_success_threshold; int amrr_min_success_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_MSG_RATECTL ; 
 int /*<<< orphan*/  IEEE80211_NOTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_node*,char*,int,scalar_t__,scalar_t__) ; 
 int IEEE80211_RATE_VAL ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ amrr_node_is_11n (struct ieee80211_node*) ; 
 int /*<<< orphan*/  is_enough (struct ieee80211_amrr_node*) ; 
 scalar_t__ is_failure (struct ieee80211_amrr_node*) ; 
 scalar_t__ is_success (struct ieee80211_amrr_node*) ; 

__attribute__((used)) static int
amrr_update(struct ieee80211_amrr *amrr, struct ieee80211_amrr_node *amn,
    struct ieee80211_node *ni)
{
	int rix = amn->amn_rix;
	const struct ieee80211_rateset *rs = NULL;

	KASSERT(is_enough(amn), ("txcnt %d", amn->amn_txcnt));

	/* 11n or not? Pick the right rateset */
	if (amrr_node_is_11n(ni)) {
		/* XXX ew */
		rs = (struct ieee80211_rateset *) &ni->ni_htrates;
	} else {
		rs = &ni->ni_rates;
	}

	/* XXX TODO: we really need a rate-to-string method */
	/* XXX TODO: non-11n rate should be divided by two.. */
	IEEE80211_NOTE(ni->ni_vap, IEEE80211_MSG_RATECTL, ni,
	    "AMRR: current rate %d, txcnt=%d, retrycnt=%d",
	    rs->rs_rates[rix] & IEEE80211_RATE_VAL,
	    amn->amn_txcnt,
	    amn->amn_retrycnt);

	/*
	 * XXX This is totally bogus for 11n, as although high MCS
	 * rates for each stream may be failing, the next stream
	 * should be checked.
	 *
	 * Eg, if MCS5 is ok but MCS6/7 isn't, and we can go up to
	 * MCS23, we should skip 6/7 and try 8 onwards.
	 */
	if (is_success(amn)) {
		amn->amn_success++;
		if (amn->amn_success >= amn->amn_success_threshold &&
		    rix + 1 < rs->rs_nrates) {
			amn->amn_recovery = 1;
			amn->amn_success = 0;
			rix++;
			/* XXX TODO: we really need a rate-to-string method */
			/* XXX TODO: non-11n rate should be divided by two.. */
			IEEE80211_NOTE(ni->ni_vap, IEEE80211_MSG_RATECTL, ni,
			    "AMRR increasing rate %d (txcnt=%d retrycnt=%d)",
			    rs->rs_rates[rix] & IEEE80211_RATE_VAL,
			    amn->amn_txcnt, amn->amn_retrycnt);
		} else {
			amn->amn_recovery = 0;
		}
	} else if (is_failure(amn)) {
		amn->amn_success = 0;
		if (rix > 0) {
			if (amn->amn_recovery) {
				amn->amn_success_threshold *= 2;
				if (amn->amn_success_threshold >
				    amrr->amrr_max_success_threshold)
					amn->amn_success_threshold =
					    amrr->amrr_max_success_threshold;
			} else {
				amn->amn_success_threshold =
				    amrr->amrr_min_success_threshold;
			}
			rix--;
			/* XXX TODO: we really need a rate-to-string method */
			/* XXX TODO: non-11n rate should be divided by two.. */
			IEEE80211_NOTE(ni->ni_vap, IEEE80211_MSG_RATECTL, ni,
			    "AMRR decreasing rate %d (txcnt=%d retrycnt=%d)",
			    rs->rs_rates[rix] & IEEE80211_RATE_VAL,
			    amn->amn_txcnt, amn->amn_retrycnt);
		}
		amn->amn_recovery = 0;
	}

	/* reset counters */
	amn->amn_txcnt = 0;
	amn->amn_retrycnt = 0;

	return rix;
}