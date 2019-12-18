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
struct ieee80211vap {struct ieee80211_key* iv_nw_keys; } ;
struct ieee80211_key {int wk_flags; } ;
typedef  scalar_t__ ieee80211_keyix ;

/* Variables and functions */
 scalar_t__ IEEE80211_KEYIX_NONE ; 
 int IEEE80211_KEY_GROUP ; 
 size_t IEEE80211_WEP_NKID ; 
 scalar_t__ ieee80211_crypto_get_key_wepidx (struct ieee80211vap*,struct ieee80211_key*) ; 

__attribute__((used)) static int
null_key_alloc(struct ieee80211vap *vap, struct ieee80211_key *k,
	ieee80211_keyix *keyix, ieee80211_keyix *rxkeyix)
{
	if (!(&vap->iv_nw_keys[0] <= k &&
	     k < &vap->iv_nw_keys[IEEE80211_WEP_NKID])) {
		/*
		 * Not in the global key table, the driver should handle this
		 * by allocating a slot in the h/w key table/cache.  In
		 * lieu of that return key slot 0 for any unicast key
		 * request.  We disallow the request if this is a group key.
		 * This default policy does the right thing for legacy hardware
		 * with a 4 key table.  It also handles devices that pass
		 * packets through untouched when marked with the WEP bit
		 * and key index 0.
		 */
		if (k->wk_flags & IEEE80211_KEY_GROUP)
			return 0;
		*keyix = 0;	/* NB: use key index 0 for ucast key */
	} else {
		*keyix = ieee80211_crypto_get_key_wepidx(vap, k);
	}
	*rxkeyix = IEEE80211_KEYIX_NONE;	/* XXX maybe *keyix? */
	return 1;
}