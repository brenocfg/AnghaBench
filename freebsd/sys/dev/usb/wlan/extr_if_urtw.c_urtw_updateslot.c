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
struct urtw_softc {int /*<<< orphan*/  sc_updateslot_task; } ;
struct ieee80211com {struct urtw_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_runtask (struct ieee80211com*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
urtw_updateslot(struct ieee80211com *ic)
{
	struct urtw_softc *sc = ic->ic_softc;

	ieee80211_runtask(ic, &sc->sc_updateslot_task);
}