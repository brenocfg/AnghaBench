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
struct wtap_softc {int up; } ;
struct ieee80211com {scalar_t__ ic_nrunning; struct wtap_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_start_all (struct ieee80211com*) ; 

__attribute__((used)) static void
wtap_parent(struct ieee80211com *ic)
{
	struct wtap_softc *sc = ic->ic_softc;

	if (ic->ic_nrunning > 0) {
		sc->up = 1;
		ieee80211_start_all(ic);
	} else
		sc->up = 0;
}