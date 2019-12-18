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
struct rtwn_vap {struct ieee80211_key** keys; } ;
struct rtwn_softc {scalar_t__ sc_hwcrypto; } ;
struct ieee80211_key {int dummy; } ;

/* Variables and functions */
 int IEEE80211_WEP_NKID ; 
 scalar_t__ RTWN_CRYPTO_FULL ; 
 int rtwn_key_set_cb0 (struct rtwn_softc*,struct ieee80211_key const*) ; 

int
rtwn_init_static_keys(struct rtwn_softc *sc, struct rtwn_vap *rvp)
{
	int i, error;

	if (sc->sc_hwcrypto != RTWN_CRYPTO_FULL)
		return (0);		/* nothing to do */

	for (i = 0; i < IEEE80211_WEP_NKID; i++) {
		const struct ieee80211_key *k = rvp->keys[i];
		if (k != NULL) {
			error = rtwn_key_set_cb0(sc, k);
			if (error != 0)
				return (error);
		}
	}

	return (0);
}