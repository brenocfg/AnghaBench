#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ieee80211vap {int /*<<< orphan*/  iv_bss; TYPE_1__* iv_ic; } ;
struct TYPE_5__ {int /*<<< orphan*/  wk_macaddr; int /*<<< orphan*/  wk_flags; void* wk_rxkeyix; void* wk_keyix; } ;
struct ieee80211_node {TYPE_2__ ni_ucastkey; int /*<<< orphan*/  ni_macaddr; struct ieee80211vap* ni_vap; } ;
struct ath_softc {int dummy; } ;
typedef  void* ieee80211_keyix ;
struct TYPE_4__ {struct ath_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_ADDR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IEEE80211_KEY_DEVKEY ; 
 int /*<<< orphan*/  ath_key_alloc (struct ieee80211vap*,TYPE_2__*,void**,void**) ; 
 int /*<<< orphan*/  ath_keyset (struct ath_softc*,struct ieee80211vap*,TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ath_setup_stationkey(struct ieee80211_node *ni)
{
	struct ieee80211vap *vap = ni->ni_vap;
	struct ath_softc *sc = vap->iv_ic->ic_softc;
	ieee80211_keyix keyix, rxkeyix;

	/* XXX should take a locked ref to vap->iv_bss */
	if (!ath_key_alloc(vap, &ni->ni_ucastkey, &keyix, &rxkeyix)) {
		/*
		 * Key cache is full; we'll fall back to doing
		 * the more expensive lookup in software.  Note
		 * this also means no h/w compression.
		 */
		/* XXX msg+statistic */
	} else {
		/* XXX locking? */
		ni->ni_ucastkey.wk_keyix = keyix;
		ni->ni_ucastkey.wk_rxkeyix = rxkeyix;
		/* NB: must mark device key to get called back on delete */
		ni->ni_ucastkey.wk_flags |= IEEE80211_KEY_DEVKEY;
		IEEE80211_ADDR_COPY(ni->ni_ucastkey.wk_macaddr, ni->ni_macaddr);
		/* NB: this will create a pass-thru key entry */
		ath_keyset(sc, vap, &ni->ni_ucastkey, vap->iv_bss);
	}
}