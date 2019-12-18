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
struct rt2661_softc {int dummy; } ;
struct ieee80211vap {TYPE_1__* iv_bss; } ;
struct ieee80211com {int /*<<< orphan*/  ic_vaps; struct rt2661_softc* ic_softc; } ;
struct TYPE_2__ {int /*<<< orphan*/  ni_bssid; } ;

/* Variables and functions */
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_enable_tsf_sync (struct rt2661_softc*) ; 
 int /*<<< orphan*/  rt2661_set_bssid (struct rt2661_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2661_scan_end(struct ieee80211com *ic)
{
	struct rt2661_softc *sc = ic->ic_softc;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);

	rt2661_enable_tsf_sync(sc);
	/* XXX keep local copy */
	rt2661_set_bssid(sc, vap->iv_bss->ni_bssid);
}