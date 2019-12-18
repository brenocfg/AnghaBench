#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {int dummy; } ;
struct ieee80211_key {TYPE_1__* wk_cipher; } ;
struct TYPE_2__ {void* (* ic_attach ) (struct ieee80211vap*,struct ieee80211_key*) ;} ;

/* Variables and functions */
 void* stub1 (struct ieee80211vap*,struct ieee80211_key*) ; 

__attribute__((used)) static __inline void *
cipher_attach(struct ieee80211vap *vap, struct ieee80211_key *key)
{
	return key->wk_cipher->ic_attach(vap, key);
}