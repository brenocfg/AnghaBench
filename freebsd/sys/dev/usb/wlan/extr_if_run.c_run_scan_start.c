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
struct run_softc {int dummy; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 int /*<<< orphan*/  ieee80211broadcastaddr ; 
 int /*<<< orphan*/  run_disable_tsf (struct run_softc*) ; 
 int /*<<< orphan*/  run_set_bssid (struct run_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run_scan_start(struct ieee80211com *ic)
{
	struct run_softc *sc = ic->ic_softc;

	RUN_LOCK(sc);

	/* abort TSF synchronization */
	run_disable_tsf(sc);
	run_set_bssid(sc, ieee80211broadcastaddr);

	RUN_UNLOCK(sc);

	return;
}