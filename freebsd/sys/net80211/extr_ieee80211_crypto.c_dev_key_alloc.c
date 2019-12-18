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
struct ieee80211vap {int (* iv_key_alloc ) (struct ieee80211vap*,struct ieee80211_key*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct ieee80211_key {int dummy; } ;
typedef  int /*<<< orphan*/  ieee80211_keyix ;

/* Variables and functions */
 int stub1 (struct ieee80211vap*,struct ieee80211_key*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline int
dev_key_alloc(struct ieee80211vap *vap,
	struct ieee80211_key *key,
	ieee80211_keyix *keyix, ieee80211_keyix *rxkeyix)
{
	return vap->iv_key_alloc(vap, key, keyix, rxkeyix);
}