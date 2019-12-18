#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ieee80211_key {int wk_flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  keyFlags; } ;
typedef  TYPE_1__ MWL_HAL_KEYVAL ;

/* Variables and functions */
 int IEEE80211_KEY_GROUP ; 
 int IEEE80211_KEY_RECV ; 
 int IEEE80211_KEY_XMIT ; 
 int /*<<< orphan*/  KEY_FLAG_RXGROUPKEY ; 
 int /*<<< orphan*/  KEY_FLAG_TXGROUPKEY ; 

__attribute__((used)) static __inline int
addgroupflags(MWL_HAL_KEYVAL *hk, const struct ieee80211_key *k)
{
	if (k->wk_flags & IEEE80211_KEY_GROUP) {
		if (k->wk_flags & IEEE80211_KEY_XMIT)
			hk->keyFlags |= KEY_FLAG_TXGROUPKEY;
		if (k->wk_flags & IEEE80211_KEY_RECV)
			hk->keyFlags |= KEY_FLAG_RXGROUPKEY;
		return 1;
	} else
		return 0;
}