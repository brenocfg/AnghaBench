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
struct ieee80211vap {size_t iv_def_txkey; struct ieee80211_key* iv_nw_keys; } ;
struct ieee80211_node {int dummy; } ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 size_t IEEE80211_KEYIX_NONE ; 
 scalar_t__ IEEE80211_KEY_UNDEFINED (struct ieee80211_key*) ; 

__attribute__((used)) static __inline struct ieee80211_key *
ieee80211_crypto_getmcastkey(struct ieee80211vap *vap,
	struct ieee80211_node *ni)
{
	if (vap->iv_def_txkey == IEEE80211_KEYIX_NONE ||
	    IEEE80211_KEY_UNDEFINED(&vap->iv_nw_keys[vap->iv_def_txkey]))
		return NULL;
	return &vap->iv_nw_keys[vap->iv_def_txkey];
}