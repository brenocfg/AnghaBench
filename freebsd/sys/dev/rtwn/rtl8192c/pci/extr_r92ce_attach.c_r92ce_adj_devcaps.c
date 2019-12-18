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
struct ieee80211com {int /*<<< orphan*/  ic_caps; } ;
struct rtwn_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_C_PMGT ; 

__attribute__((used)) static void
r92ce_adj_devcaps(struct rtwn_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	/*
	 * XXX do NOT enable PMGT until RSVD_PAGE command
	 * will not be tested / fixed + HRPWM register must be set too.
	 */
	ic->ic_caps &= ~IEEE80211_C_PMGT;
}