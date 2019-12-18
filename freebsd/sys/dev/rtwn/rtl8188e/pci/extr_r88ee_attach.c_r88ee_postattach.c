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
struct ieee80211com {int /*<<< orphan*/  ic_scan_end; int /*<<< orphan*/  ic_scan_start; } ;
struct rtwn_softc {struct ieee80211com sc_ic; struct r92c_softc* sc_priv; } ;
struct r92c_softc {int /*<<< orphan*/  rs_scan_end; int /*<<< orphan*/  rs_scan_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  r92c_scan_end ; 
 int /*<<< orphan*/  r92c_scan_start ; 

__attribute__((used)) static void
r88ee_postattach(struct rtwn_softc *sc)
{
	struct r92c_softc *rs = sc->sc_priv;
	struct ieee80211com *ic = &sc->sc_ic;

	rs->rs_scan_start = ic->ic_scan_start;
	ic->ic_scan_start = r92c_scan_start;
	rs->rs_scan_end = ic->ic_scan_end;
	ic->ic_scan_end = r92c_scan_end;
}