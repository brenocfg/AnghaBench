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
struct ieee80211vap {int (* iv_key_delete ) (struct ieee80211vap*,struct ieee80211_key const*) ;} ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 int stub1 (struct ieee80211vap*,struct ieee80211_key const*) ; 

__attribute__((used)) static __inline int
dev_key_delete(struct ieee80211vap *vap,
	const struct ieee80211_key *key)
{
	return vap->iv_key_delete(vap, key);
}