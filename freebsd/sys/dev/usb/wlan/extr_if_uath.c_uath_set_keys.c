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
struct uath_softc {int dummy; } ;
struct ieee80211vap {size_t iv_def_txkey; struct ieee80211_key const* iv_nw_keys; } ;
typedef  struct ieee80211_key {int wk_flags; } const ieee80211_key ;

/* Variables and functions */
 size_t IEEE80211_KEYIX_NONE ; 
 int IEEE80211_KEY_RECV ; 
 int IEEE80211_KEY_XMIT ; 
 int IEEE80211_WEP_NKID ; 
 int UATH_DEFAULT_KEY ; 
 int uath_set_key (struct uath_softc*,struct ieee80211_key const*,int) ; 

__attribute__((used)) static int
uath_set_keys(struct uath_softc *sc, struct ieee80211vap *vap)
{
	int i, error;

	error = 0;
	for (i = 0; i < IEEE80211_WEP_NKID; i++) {
		const struct ieee80211_key *wk = &vap->iv_nw_keys[i];

		if (wk->wk_flags & (IEEE80211_KEY_XMIT|IEEE80211_KEY_RECV)) {
			error = uath_set_key(sc, wk, i);
			if (error)
				return (error);
		}
	}
	if (vap->iv_def_txkey != IEEE80211_KEYIX_NONE) {
		error = uath_set_key(sc, &vap->iv_nw_keys[vap->iv_def_txkey],
			UATH_DEFAULT_KEY);
	}
	return (error);
}