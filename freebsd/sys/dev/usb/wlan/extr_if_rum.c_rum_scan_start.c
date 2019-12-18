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
struct rum_softc {int dummy; } ;
struct ieee80211com {struct rum_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  ieee80211broadcastaddr ; 
 int /*<<< orphan*/  rum_abort_tsf_sync (struct rum_softc*) ; 
 int /*<<< orphan*/  rum_set_bssid (struct rum_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rum_scan_start(struct ieee80211com *ic)
{
	struct rum_softc *sc = ic->ic_softc;

	RUM_LOCK(sc);
	rum_abort_tsf_sync(sc);
	rum_set_bssid(sc, ieee80211broadcastaddr);
	RUM_UNLOCK(sc);

}