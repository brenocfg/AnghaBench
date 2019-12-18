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
typedef  int uint32_t ;
struct ieee80211vap {int iv_flags_vht; int /*<<< orphan*/  iv_vhtcaps; } ;
struct ieee80211_node {int ni_flags; scalar_t__ ni_vht_chanwidth; struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int IEEE80211_CHAN_HT20 ; 
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int IEEE80211_CHAN_VHT160 ; 
 int IEEE80211_CHAN_VHT20 ; 
 int IEEE80211_CHAN_VHT40D ; 
 int IEEE80211_CHAN_VHT40U ; 
 int IEEE80211_CHAN_VHT80 ; 
 int IEEE80211_CHAN_VHT80_80 ; 
 int IEEE80211_FVHT_USEVHT160 ; 
 int IEEE80211_FVHT_USEVHT40 ; 
 int IEEE80211_FVHT_USEVHT80 ; 
 int IEEE80211_FVHT_USEVHT80P80 ; 
 int IEEE80211_FVHT_VHT ; 
 int IEEE80211_NODE_VHT ; 
 int /*<<< orphan*/  IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK ; 
 scalar_t__ IEEE80211_VHT_CHANWIDTH_160MHZ ; 
 scalar_t__ IEEE80211_VHT_CHANWIDTH_80MHZ ; 
 scalar_t__ IEEE80211_VHT_CHANWIDTH_80P80MHZ ; 
 scalar_t__ IEEE80211_VHT_CHANWIDTH_USE_HT ; 
 int MS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t
ieee80211_vht_get_vhtflags(struct ieee80211_node *ni, uint32_t htflags)
{
	struct ieee80211vap *vap = ni->ni_vap;
	uint32_t vhtflags = 0;

	vhtflags = 0;
	if (ni->ni_flags & IEEE80211_NODE_VHT && vap->iv_flags_vht & IEEE80211_FVHT_VHT) {
		if ((ni->ni_vht_chanwidth == IEEE80211_VHT_CHANWIDTH_160MHZ) &&
		    /* XXX 2 means "160MHz and 80+80MHz", 1 means "160MHz" */
		    (MS(vap->iv_vhtcaps,
		     IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK) >= 1) &&
		    (vap->iv_flags_vht & IEEE80211_FVHT_USEVHT160)) {
			vhtflags = IEEE80211_CHAN_VHT160;
			/* Mirror the HT40 flags */
			if (htflags == IEEE80211_CHAN_HT40U) {
				vhtflags |= IEEE80211_CHAN_HT40U;
			} else if (htflags == IEEE80211_CHAN_HT40D) {
				vhtflags |= IEEE80211_CHAN_HT40D;
			}
		} else if ((ni->ni_vht_chanwidth == IEEE80211_VHT_CHANWIDTH_80P80MHZ) &&
		    /* XXX 2 means "160MHz and 80+80MHz" */
		    (MS(vap->iv_vhtcaps,
		     IEEE80211_VHTCAP_SUPP_CHAN_WIDTH_MASK) == 2) &&
		    (vap->iv_flags_vht & IEEE80211_FVHT_USEVHT80P80)) {
			vhtflags = IEEE80211_CHAN_VHT80_80;
			/* Mirror the HT40 flags */
			if (htflags == IEEE80211_CHAN_HT40U) {
				vhtflags |= IEEE80211_CHAN_HT40U;
			} else if (htflags == IEEE80211_CHAN_HT40D) {
				vhtflags |= IEEE80211_CHAN_HT40D;
			}
		} else if ((ni->ni_vht_chanwidth == IEEE80211_VHT_CHANWIDTH_80MHZ) &&
		    (vap->iv_flags_vht & IEEE80211_FVHT_USEVHT80)) {
			vhtflags = IEEE80211_CHAN_VHT80;
			/* Mirror the HT40 flags */
			if (htflags == IEEE80211_CHAN_HT40U) {
				vhtflags |= IEEE80211_CHAN_HT40U;
			} else if (htflags == IEEE80211_CHAN_HT40D) {
				vhtflags |= IEEE80211_CHAN_HT40D;
			}
		} else if (ni->ni_vht_chanwidth == IEEE80211_VHT_CHANWIDTH_USE_HT) {
			/* Mirror the HT40 flags */
			/*
			 * XXX TODO: if ht40 is disabled, but vht40 isn't
			 * disabled then this logic will get very, very sad.
			 * It's quite possible the only sane thing to do is
			 * to not have vht40 as an option, and just obey
			 * 'ht40' as that flag.
			 */
			if ((htflags == IEEE80211_CHAN_HT40U) &&
			    (vap->iv_flags_vht & IEEE80211_FVHT_USEVHT40)) {
				vhtflags = IEEE80211_CHAN_VHT40U
				    | IEEE80211_CHAN_HT40U;
			} else if (htflags == IEEE80211_CHAN_HT40D &&
			    (vap->iv_flags_vht & IEEE80211_FVHT_USEVHT40)) {
				vhtflags = IEEE80211_CHAN_VHT40D
				    | IEEE80211_CHAN_HT40D;
			} else if (htflags == IEEE80211_CHAN_HT20) {
				vhtflags = IEEE80211_CHAN_VHT20
				    | IEEE80211_CHAN_HT20;
			}
		} else {
			vhtflags = IEEE80211_CHAN_VHT20;
		}
	}
	return (vhtflags);
}