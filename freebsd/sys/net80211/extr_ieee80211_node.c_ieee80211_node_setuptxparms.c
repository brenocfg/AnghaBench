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
struct ieee80211vap {int /*<<< orphan*/ * iv_txparms; } ;
struct ieee80211_node {int ni_flags; int /*<<< orphan*/ * ni_txparms; int /*<<< orphan*/  ni_chan; struct ieee80211vap* ni_vap; } ;
typedef  enum ieee80211_phymode { ____Placeholder_ieee80211_phymode } ieee80211_phymode ;

/* Variables and functions */
 scalar_t__ IEEE80211_IS_CHAN_108G (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_5GHZ (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_A (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_HALF (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_QUARTER (int /*<<< orphan*/ ) ; 
 scalar_t__ IEEE80211_IS_CHAN_ST (int /*<<< orphan*/ ) ; 
 int IEEE80211_MODE_11A ; 
 int IEEE80211_MODE_11B ; 
 int IEEE80211_MODE_11G ; 
 int IEEE80211_MODE_11NA ; 
 int IEEE80211_MODE_11NG ; 
 int IEEE80211_MODE_HALF ; 
 int IEEE80211_MODE_QUARTER ; 
 int IEEE80211_MODE_STURBO_A ; 
 int IEEE80211_MODE_VHT_2GHZ ; 
 int IEEE80211_MODE_VHT_5GHZ ; 
 int IEEE80211_NODE_ERP ; 
 int IEEE80211_NODE_HT ; 
 int IEEE80211_NODE_VHT ; 

void
ieee80211_node_setuptxparms(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	enum ieee80211_phymode mode;

	if (ni->ni_flags & IEEE80211_NODE_VHT) {
		if (IEEE80211_IS_CHAN_5GHZ(ni->ni_chan))
			mode = IEEE80211_MODE_VHT_5GHZ;
		else
			mode = IEEE80211_MODE_VHT_2GHZ;
	} else if (ni->ni_flags & IEEE80211_NODE_HT) {
		if (IEEE80211_IS_CHAN_5GHZ(ni->ni_chan))
			mode = IEEE80211_MODE_11NA;
		else
			mode = IEEE80211_MODE_11NG;
	} else {				/* legacy rate handling */
		if (IEEE80211_IS_CHAN_ST(ni->ni_chan))
			mode = IEEE80211_MODE_STURBO_A;
		else if (IEEE80211_IS_CHAN_HALF(ni->ni_chan))
			mode = IEEE80211_MODE_HALF;
		else if (IEEE80211_IS_CHAN_QUARTER(ni->ni_chan))
			mode = IEEE80211_MODE_QUARTER;
		/* NB: 108A should be handled as 11a */
		else if (IEEE80211_IS_CHAN_A(ni->ni_chan))
			mode = IEEE80211_MODE_11A;
		else if (IEEE80211_IS_CHAN_108G(ni->ni_chan) ||
		    (ni->ni_flags & IEEE80211_NODE_ERP))
			mode = IEEE80211_MODE_11G;
		else
			mode = IEEE80211_MODE_11B;
	}
	ni->ni_txparms = &vap->iv_txparms[mode];
}