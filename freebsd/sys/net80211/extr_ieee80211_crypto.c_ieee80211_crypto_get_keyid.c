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
typedef  int uint8_t ;
struct ieee80211vap {struct ieee80211_key* iv_nw_keys; } ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 size_t IEEE80211_WEP_NKID ; 

uint8_t
ieee80211_crypto_get_keyid(struct ieee80211vap *vap, struct ieee80211_key *k)
{
	if (k >= &vap->iv_nw_keys[0] &&
	    k <  &vap->iv_nw_keys[IEEE80211_WEP_NKID])
		return (k - vap->iv_nw_keys);
	else
		return (0);
}