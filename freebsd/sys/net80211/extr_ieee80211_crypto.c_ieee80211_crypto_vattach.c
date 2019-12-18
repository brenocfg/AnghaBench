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
struct ieee80211vap {int iv_max_keyix; void* iv_key_update_end; void* iv_key_update_begin; int /*<<< orphan*/  iv_key_delete; int /*<<< orphan*/  iv_key_set; int /*<<< orphan*/  iv_key_alloc; int /*<<< orphan*/ * iv_nw_keys; int /*<<< orphan*/  iv_def_txkey; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_KEYIX_NONE ; 
 int IEEE80211_WEP_NKID ; 
 int /*<<< orphan*/  ieee80211_crypto_resetkey (struct ieee80211vap*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  null_key_alloc ; 
 int /*<<< orphan*/  null_key_delete ; 
 int /*<<< orphan*/  null_key_set ; 
 void* null_key_update ; 

void
ieee80211_crypto_vattach(struct ieee80211vap *vap)
{
	int i;

	/* NB: we assume everything is pre-zero'd */
	vap->iv_max_keyix = IEEE80211_WEP_NKID;
	vap->iv_def_txkey = IEEE80211_KEYIX_NONE;
	for (i = 0; i < IEEE80211_WEP_NKID; i++)
		ieee80211_crypto_resetkey(vap, &vap->iv_nw_keys[i],
			IEEE80211_KEYIX_NONE);
	/*
	 * Initialize the driver key support routines to noop entries.
	 * This is useful especially for the cipher test modules.
	 */
	vap->iv_key_alloc = null_key_alloc;
	vap->iv_key_set = null_key_set;
	vap->iv_key_delete = null_key_delete;
	vap->iv_key_update_begin = null_key_update;
	vap->iv_key_update_end = null_key_update;
}