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
struct zyd_softc {int /*<<< orphan*/  sc_bssid; } ;
struct ieee80211com {struct zyd_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZYD_LOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  ZYD_UNLOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  zyd_set_bssid (struct zyd_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zyd_scan_end(struct ieee80211com *ic)
{
	struct zyd_softc *sc = ic->ic_softc;

	ZYD_LOCK(sc);
	/* restore previous bssid */
	zyd_set_bssid(sc, sc->sc_bssid);
	ZYD_UNLOCK(sc);
}