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
struct ieee80211com {int /*<<< orphan*/  ic_sta; } ;
struct ieee80211_node {int dummy; } ;
struct ath_softc {struct ieee80211com sc_ic; } ;
struct TYPE_2__ {int /*<<< orphan*/  macaddr; } ;
struct ath_rateioctl {TYPE_1__ is_u; } ;
struct ath_node {int dummy; } ;

/* Variables and functions */
 struct ath_node* ATH_NODE (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ATH_NODE_LOCK (struct ath_node*) ; 
 int /*<<< orphan*/  ATH_NODE_UNLOCK (struct ath_node*) ; 
 int EINVAL ; 
 int ath_rate_fetch_node_stats (struct ath_softc*,struct ath_node*,struct ath_rateioctl*) ; 
 struct ieee80211_node* ieee80211_find_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_node_decref (struct ieee80211_node*) ; 

__attribute__((used)) static int
ath_ioctl_ratestats(struct ath_softc *sc, struct ath_rateioctl *rs)
{
	struct ath_node *an;
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211_node *ni;
	int error = 0;

	/* Perform a lookup on the given node */
	ni = ieee80211_find_node(&ic->ic_sta, rs->is_u.macaddr);
	if (ni == NULL) {
		error = EINVAL;
		goto bad;
	}

	/* Lock the ath_node */
	an = ATH_NODE(ni);
	ATH_NODE_LOCK(an);

	/* Fetch the rate control stats for this node */
	error = ath_rate_fetch_node_stats(sc, an, rs);

	/* No matter what happens here, just drop through */

	/* Unlock the ath_node */
	ATH_NODE_UNLOCK(an);

	/* Unref the node */
	ieee80211_node_decref(ni);

bad:
	return (error);
}