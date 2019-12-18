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
struct ieee80211vap {int /*<<< orphan*/  iv_bss; TYPE_1__* iv_ic; } ;
struct ieee80211_key {int dummy; } ;
struct ath_softc {int dummy; } ;
struct TYPE_2__ {struct ath_softc* ic_softc; } ;

/* Variables and functions */
 int ath_keyset (struct ath_softc*,struct ieee80211vap*,struct ieee80211_key const*,int /*<<< orphan*/ ) ; 

int
ath_key_set(struct ieee80211vap *vap, const struct ieee80211_key *k)
{
	struct ath_softc *sc = vap->iv_ic->ic_softc;

	return ath_keyset(sc, vap, k, vap->iv_bss);
}