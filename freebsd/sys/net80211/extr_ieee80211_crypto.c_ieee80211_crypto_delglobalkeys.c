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
struct ieee80211vap {int /*<<< orphan*/ * iv_nw_keys; } ;

/* Variables and functions */
 int IEEE80211_WEP_NKID ; 
 int /*<<< orphan*/  _ieee80211_crypto_delkey (struct ieee80211vap*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_key_update_begin (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_key_update_end (struct ieee80211vap*) ; 

void
ieee80211_crypto_delglobalkeys(struct ieee80211vap *vap)
{
	int i;

	ieee80211_key_update_begin(vap);
	for (i = 0; i < IEEE80211_WEP_NKID; i++)
		(void) _ieee80211_crypto_delkey(vap, &vap->iv_nw_keys[i]);
	ieee80211_key_update_end(vap);
}