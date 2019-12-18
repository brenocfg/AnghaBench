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
struct sbuf {int dummy; } ;
struct ieee80211_rateset {int* rs_rates; } ;
struct ieee80211_node {struct ieee80211_rateset ni_rates; int /*<<< orphan*/  ni_htrates; struct ieee80211_amrr_node* ni_rctls; } ;
struct ieee80211_amrr_node {size_t amn_rix; int amn_ticks; int amn_txcnt; int amn_success; int amn_success_threshold; int amn_recovery; int amn_retrycnt; } ;

/* Variables and functions */
 int IEEE80211_RATE_VAL ; 
 scalar_t__ amrr_node_is_11n (struct ieee80211_node*) ; 
 int /*<<< orphan*/  sbuf_printf (struct sbuf*,char*,int) ; 

__attribute__((used)) static void
amrr_node_stats(struct ieee80211_node *ni, struct sbuf *s)
{
	int rate;
	struct ieee80211_amrr_node *amn = ni->ni_rctls;
	struct ieee80211_rateset *rs;

	/* XXX TODO: check locking? */

	if (!amn)
		return;

	/* XXX TODO: this should be a method */
	if (amrr_node_is_11n(ni)) {
		rs = (struct ieee80211_rateset *) &ni->ni_htrates;
		rate = rs->rs_rates[amn->amn_rix] & IEEE80211_RATE_VAL;
		sbuf_printf(s, "rate: MCS %d\n", rate);
	} else {
		rs = &ni->ni_rates;
		rate = rs->rs_rates[amn->amn_rix] & IEEE80211_RATE_VAL;
		sbuf_printf(s, "rate: %d Mbit\n", rate / 2);
	}

	sbuf_printf(s, "ticks: %d\n", amn->amn_ticks);
	sbuf_printf(s, "txcnt: %u\n", amn->amn_txcnt);
	sbuf_printf(s, "success: %u\n", amn->amn_success);
	sbuf_printf(s, "success_threshold: %u\n", amn->amn_success_threshold);
	sbuf_printf(s, "recovery: %u\n", amn->amn_recovery);
	sbuf_printf(s, "retry_cnt: %u\n", amn->amn_retrycnt);
}