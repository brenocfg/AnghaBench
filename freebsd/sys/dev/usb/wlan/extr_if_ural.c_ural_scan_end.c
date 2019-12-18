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
struct ural_softc {int /*<<< orphan*/  sc_bssid; } ;
struct ieee80211com {struct ural_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_enable_tsf_sync (struct ural_softc*) ; 
 int /*<<< orphan*/  ural_set_bssid (struct ural_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ural_scan_end(struct ieee80211com *ic)
{
	struct ural_softc *sc = ic->ic_softc;

	RAL_LOCK(sc);
	ural_enable_tsf_sync(sc);
	ural_set_bssid(sc, sc->sc_bssid);
	RAL_UNLOCK(sc);

}