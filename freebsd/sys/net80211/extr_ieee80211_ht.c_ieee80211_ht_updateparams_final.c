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
typedef  int /*<<< orphan*/  uint8_t ;
struct ieee80211vap {int iv_flags_ht; } ;
struct ieee80211_node {scalar_t__ ni_ht2ndchan; struct ieee80211vap* ni_vap; } ;
struct ieee80211_ie_htinfo {int hi_byte1; } ;

/* Variables and functions */
 int IEEE80211_CHAN_HT20 ; 
 int IEEE80211_CHAN_HT40D ; 
 int IEEE80211_CHAN_HT40U ; 
 int IEEE80211_FHT_HT ; 
 int IEEE80211_FHT_USEHT40 ; 
 scalar_t__ IEEE80211_HTINFO_2NDCHAN_ABOVE ; 
 scalar_t__ IEEE80211_HTINFO_2NDCHAN_BELOW ; 
 int IEEE80211_HTINFO_TXWIDTH_2040 ; 
 scalar_t__ htinfo_update_chw (struct ieee80211_node*,int,int) ; 
 int ieee80211_vht_get_vhtflags (struct ieee80211_node*,int) ; 

int
ieee80211_ht_updateparams_final(struct ieee80211_node *ni,
	const uint8_t *htcapie, const uint8_t *htinfoie)
{
	struct ieee80211vap *vap = ni->ni_vap;
	const struct ieee80211_ie_htinfo *htinfo;
	int htflags, vhtflags;
	int ret = 0;

	htinfo = (const struct ieee80211_ie_htinfo *) htinfoie;

	htflags = (vap->iv_flags_ht & IEEE80211_FHT_HT) ?
	    IEEE80211_CHAN_HT20 : 0;

	/* NB: honor operating mode constraint */
	if ((htinfo->hi_byte1 & IEEE80211_HTINFO_TXWIDTH_2040) &&
	    (vap->iv_flags_ht & IEEE80211_FHT_USEHT40)) {
		if (ni->ni_ht2ndchan == IEEE80211_HTINFO_2NDCHAN_ABOVE)
			htflags = IEEE80211_CHAN_HT40U;
		else if (ni->ni_ht2ndchan == IEEE80211_HTINFO_2NDCHAN_BELOW)
			htflags = IEEE80211_CHAN_HT40D;
	}

	/*
	 * VHT flags - do much the same; check whether VHT is available
	 * and if so, what our ideal channel use would be based on our
	 * capabilities and the (pre-parsed) VHT info IE.
	 */
	vhtflags = ieee80211_vht_get_vhtflags(ni, htflags);

	if (htinfo_update_chw(ni, htflags, vhtflags))
		ret = 1;

	return (ret);
}