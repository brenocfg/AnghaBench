#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct rt2560_softc {int dummy; } ;
struct ieee80211vap {TYPE_2__* iv_bss; } ;
struct ieee80211com {TYPE_1__* ic_scan; struct rt2560_softc* ic_softc; } ;
struct TYPE_4__ {int /*<<< orphan*/  ni_bssid; } ;
struct TYPE_3__ {struct ieee80211vap* ss_vap; } ;

/* Variables and functions */
 int /*<<< orphan*/  rt2560_enable_tsf_sync (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_set_bssid (struct rt2560_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2560_scan_end(struct ieee80211com *ic)
{
	struct rt2560_softc *sc = ic->ic_softc;
	struct ieee80211vap *vap = ic->ic_scan->ss_vap;

	rt2560_enable_tsf_sync(sc);
	/* XXX keep local copy */
	rt2560_set_bssid(sc, vap->iv_bss->ni_bssid);
}