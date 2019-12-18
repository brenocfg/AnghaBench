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
struct run_softc {int /*<<< orphan*/  sc_bssid; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 int /*<<< orphan*/  run_enable_tsf_sync (struct run_softc*) ; 
 int /*<<< orphan*/  run_set_bssid (struct run_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_scan_end(struct ieee80211com *ic)
{
	struct run_softc *sc = ic->ic_softc;

	RUN_LOCK(sc);

	run_enable_tsf_sync(sc);
	run_set_bssid(sc, sc->sc_bssid);

	RUN_UNLOCK(sc);

	return;
}