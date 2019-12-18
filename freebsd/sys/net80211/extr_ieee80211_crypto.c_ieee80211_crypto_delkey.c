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
struct ieee80211vap {int dummy; } ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 int _ieee80211_crypto_delkey (struct ieee80211vap*,struct ieee80211_key*) ; 
 int /*<<< orphan*/  ieee80211_key_update_begin (struct ieee80211vap*) ; 
 int /*<<< orphan*/  ieee80211_key_update_end (struct ieee80211vap*) ; 

int
ieee80211_crypto_delkey(struct ieee80211vap *vap, struct ieee80211_key *key)
{
	int status;

	ieee80211_key_update_begin(vap);
	status = _ieee80211_crypto_delkey(vap, key);
	ieee80211_key_update_end(vap);
	return status;
}