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
typedef  scalar_t__ uint8_t ;
struct ieee80211vap {int iv_htcaps; int iv_flags_ht; } ;
struct ieee80211_node {int /*<<< orphan*/  ni_flags; struct ieee80211vap* ni_vap; } ;
struct ieee80211_ie_htinfo {int hi_byte1; } ;

/* Variables and functions */
 scalar_t__ const IEEE80211_ELEMID_VENDOR ; 
 int IEEE80211_FHT_RIFS ; 
 int IEEE80211_HTC_SMPS ; 
 int IEEE80211_HTINFO_RIFSMODE_PERM ; 
 int /*<<< orphan*/  IEEE80211_NODE_RIFS ; 
 int /*<<< orphan*/  htcap_update_ldpc (struct ieee80211_node*) ; 
 int /*<<< orphan*/  htcap_update_mimo_ps (struct ieee80211_node*) ; 
 int /*<<< orphan*/  htcap_update_shortgi (struct ieee80211_node*) ; 
 int /*<<< orphan*/  htinfo_parse (struct ieee80211_node*,struct ieee80211_ie_htinfo const*) ; 
 int /*<<< orphan*/  ieee80211_parse_htcap (struct ieee80211_node*,scalar_t__ const*) ; 

void
ieee80211_ht_updateparams(struct ieee80211_node *ni,
	const uint8_t *htcapie, const uint8_t *htinfoie)
{
	struct ieee80211vap *vap = ni->ni_vap;
	const struct ieee80211_ie_htinfo *htinfo;

	ieee80211_parse_htcap(ni, htcapie);
	if (vap->iv_htcaps & IEEE80211_HTC_SMPS)
		htcap_update_mimo_ps(ni);
	htcap_update_shortgi(ni);
	htcap_update_ldpc(ni);

	if (htinfoie[0] == IEEE80211_ELEMID_VENDOR)
		htinfoie += 4;
	htinfo = (const struct ieee80211_ie_htinfo *) htinfoie;
	htinfo_parse(ni, htinfo);

	/*
	 * Defer the node channel change; we need to now
	 * update VHT parameters before we do it.
	 */

	if ((htinfo->hi_byte1 & IEEE80211_HTINFO_RIFSMODE_PERM) &&
	    (vap->iv_flags_ht & IEEE80211_FHT_RIFS))
		ni->ni_flags |= IEEE80211_NODE_RIFS;
	else
		ni->ni_flags &= ~IEEE80211_NODE_RIFS;
}