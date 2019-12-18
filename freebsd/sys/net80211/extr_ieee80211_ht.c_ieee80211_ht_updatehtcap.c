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
struct ieee80211vap {int iv_htcaps; } ;
struct ieee80211_node {struct ieee80211vap* ni_vap; } ;

/* Variables and functions */
 int IEEE80211_HTC_SMPS ; 
 int /*<<< orphan*/  htcap_update_ldpc (struct ieee80211_node*) ; 
 int /*<<< orphan*/  htcap_update_mimo_ps (struct ieee80211_node*) ; 
 int /*<<< orphan*/  htcap_update_shortgi (struct ieee80211_node*) ; 
 int /*<<< orphan*/  ieee80211_parse_htcap (struct ieee80211_node*,int /*<<< orphan*/  const*) ; 

void
ieee80211_ht_updatehtcap(struct ieee80211_node *ni, const uint8_t *htcapie)
{
	struct ieee80211vap *vap = ni->ni_vap;

	ieee80211_parse_htcap(ni, htcapie);
	if (vap->iv_htcaps & IEEE80211_HTC_SMPS)
		htcap_update_mimo_ps(ni);
	htcap_update_shortgi(ni);
	htcap_update_ldpc(ni);
}