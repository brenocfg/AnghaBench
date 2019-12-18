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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int rs_nrates; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_vap; TYPE_1__ ni_rates; } ;
struct ath_softc {int dummy; } ;
struct amrr_node {int amn_rix; int amn_success_threshold; int amn_success; int amn_recovery; scalar_t__ amn_tx_failure_cnt; scalar_t__ amn_tx_try3_cnt; scalar_t__ amn_tx_try2_cnt; scalar_t__ amn_tx_try1_cnt; scalar_t__ amn_tx_try0_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_NODE (struct ieee80211_node*) ; 
 struct amrr_node* ATH_NODE_AMRR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_MSG_RATECTL ; 
 int /*<<< orphan*/  IEEE80211_NOTE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ieee80211_node*,char*,int,...) ; 
 scalar_t__ ath_rate_max_success_threshold ; 
 int ath_rate_min_success_threshold ; 
 int /*<<< orphan*/  ath_rate_update (struct ath_softc*,struct ieee80211_node*,int) ; 
 scalar_t__ is_enough (struct amrr_node*) ; 
 scalar_t__ is_failure (struct amrr_node*) ; 
 scalar_t__ is_success (struct amrr_node*) ; 
 int min (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath_rate_ctl(void *arg, struct ieee80211_node *ni)
{
	struct ath_softc *sc = arg;
	struct amrr_node *amn = ATH_NODE_AMRR(ATH_NODE (ni));
	int rix;

#define is_success(amn) \
(amn->amn_tx_try1_cnt  < (amn->amn_tx_try0_cnt/10))
#define is_enough(amn) \
(amn->amn_tx_try0_cnt > 10)
#define is_failure(amn) \
(amn->amn_tx_try1_cnt > (amn->amn_tx_try0_cnt/3))

	rix = amn->amn_rix;
  
  	IEEE80211_NOTE(ni->ni_vap, IEEE80211_MSG_RATECTL, ni,
	    "cnt0: %d cnt1: %d cnt2: %d cnt3: %d -- threshold: %d",
	    amn->amn_tx_try0_cnt, amn->amn_tx_try1_cnt, amn->amn_tx_try2_cnt,
	    amn->amn_tx_try3_cnt, amn->amn_success_threshold);
  	if (is_success (amn) && is_enough (amn)) {
		amn->amn_success++;
		if (amn->amn_success == amn->amn_success_threshold &&
		    rix + 1 < ni->ni_rates.rs_nrates) {
  			amn->amn_recovery = 1;
  			amn->amn_success = 0;
  			rix++;
			IEEE80211_NOTE(ni->ni_vap, IEEE80211_MSG_RATECTL, ni,
			    "increase rate to %d", rix);
  		} else {
			amn->amn_recovery = 0;
		}
  	} else if (is_failure (amn)) {
  		amn->amn_success = 0;
		if (rix > 0) {
  			if (amn->amn_recovery) {
  				/* recovery failure. */
  				amn->amn_success_threshold *= 2;
  				amn->amn_success_threshold = min (amn->amn_success_threshold,
								  (u_int)ath_rate_max_success_threshold);
				IEEE80211_NOTE(ni->ni_vap,
				    IEEE80211_MSG_RATECTL, ni,
				    "decrease rate recovery thr: %d",
				    amn->amn_success_threshold);
  			} else {
  				/* simple failure. */
 				amn->amn_success_threshold = ath_rate_min_success_threshold;
				IEEE80211_NOTE(ni->ni_vap,
				    IEEE80211_MSG_RATECTL, ni,
				    "decrease rate normal thr: %d",
				    amn->amn_success_threshold);
  			}
			amn->amn_recovery = 0;
  			rix--;
   		} else {
			amn->amn_recovery = 0;
		}

   	}
	if (is_enough (amn) || rix != amn->amn_rix) {
		/* reset counters. */
		amn->amn_tx_try0_cnt = 0;
		amn->amn_tx_try1_cnt = 0;
		amn->amn_tx_try2_cnt = 0;
		amn->amn_tx_try3_cnt = 0;
		amn->amn_tx_failure_cnt = 0;
	}
	if (rix != amn->amn_rix) {
		ath_rate_update(sc, ni, rix);
	}
}