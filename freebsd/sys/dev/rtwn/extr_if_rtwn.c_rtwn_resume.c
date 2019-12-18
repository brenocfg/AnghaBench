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
struct ieee80211com {int dummy; } ;
struct rtwn_softc {struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_resume_all (struct ieee80211com*) ; 

void
rtwn_resume(struct rtwn_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	ieee80211_resume_all(ic);
}