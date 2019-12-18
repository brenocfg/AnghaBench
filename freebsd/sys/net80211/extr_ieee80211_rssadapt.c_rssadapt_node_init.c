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
struct ieee80211vap {int /*<<< orphan*/  iv_ifp; struct ieee80211_rssadapt* iv_rs; } ;
struct ieee80211_rateset {size_t rs_nrates; int* rs_rates; } ;
struct ieee80211_rssadapt_node {size_t ra_rix; int /*<<< orphan*/  ra_ticks; struct ieee80211_rateset ra_rates; struct ieee80211_rssadapt* ra_rs; } ;
struct ieee80211_rssadapt {int dummy; } ;
struct ieee80211_node {int ni_txrate; struct ieee80211vap* ni_vap; struct ieee80211_rssadapt_node* ni_rctls; struct ieee80211_rateset ni_rates; } ;

/* Variables and functions */
 struct ieee80211_rssadapt_node* IEEE80211_MALLOC (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEEE80211_MSG_RATECTL ; 
 int IEEE80211_M_NOWAIT ; 
 int IEEE80211_M_ZERO ; 
 int /*<<< orphan*/  IEEE80211_NOTE (struct ieee80211vap*,int /*<<< orphan*/ ,struct ieee80211_node*,char*,int) ; 
 int IEEE80211_RATE_VAL ; 
 int /*<<< orphan*/  M_80211_RATECTL ; 
 int /*<<< orphan*/  if_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  rssadapt_updatestats (struct ieee80211_rssadapt_node*) ; 
 int /*<<< orphan*/  ticks ; 

__attribute__((used)) static void
rssadapt_node_init(struct ieee80211_node *ni)
{
	struct ieee80211_rssadapt_node *ra;
	struct ieee80211vap *vap = ni->ni_vap;
	struct ieee80211_rssadapt *rsa = vap->iv_rs;
	const struct ieee80211_rateset *rs = &ni->ni_rates;

	if (!rsa) {
		if_printf(vap->iv_ifp, "ratectl structure was not allocated, "
		    "per-node structure allocation skipped\n");
		return;
	}

	if (ni->ni_rctls == NULL) {
		ni->ni_rctls = ra = 
		    IEEE80211_MALLOC(sizeof(struct ieee80211_rssadapt_node),
		        M_80211_RATECTL, IEEE80211_M_NOWAIT | IEEE80211_M_ZERO);
		if (ra == NULL) {
			if_printf(vap->iv_ifp, "couldn't alloc per-node ratectl "
			    "structure\n");
			return;
		}
	} else
		ra = ni->ni_rctls;
	ra->ra_rs = rsa;
	ra->ra_rates = *rs;
	rssadapt_updatestats(ra);

	/* pick initial rate */
	for (ra->ra_rix = rs->rs_nrates - 1;
	     ra->ra_rix > 0 && (rs->rs_rates[ra->ra_rix] & IEEE80211_RATE_VAL) > 72;
	     ra->ra_rix--)
		;
	ni->ni_txrate = rs->rs_rates[ra->ra_rix] & IEEE80211_RATE_VAL;
	ra->ra_ticks = ticks;

	IEEE80211_NOTE(ni->ni_vap, IEEE80211_MSG_RATECTL, ni,
	    "RSSADAPT initial rate %d", ni->ni_txrate);
}