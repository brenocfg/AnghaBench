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
struct rtwn_softc {scalar_t__ ap_vaps; scalar_t__ bcn_vaps; scalar_t__ nvaps; scalar_t__ mon_vaps; scalar_t__ vaps_running; scalar_t__ monvaps_running; int /*<<< orphan*/ ** vaps; } ;
typedef  enum ieee80211_opmode { ____Placeholder_ieee80211_opmode } ieee80211_opmode ;

/* Variables and functions */
#define  IEEE80211_M_HOSTAP 131 
#define  IEEE80211_M_IBSS 130 
#define  IEEE80211_M_MONITOR 129 
#define  IEEE80211_M_STA 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RTWN_ASSERT_LOCKED (struct rtwn_softc*) ; 
 scalar_t__ RTWN_CHIP_HAS_BCNQ1 (struct rtwn_softc*) ; 
 scalar_t__ RTWN_PORT_COUNT ; 
 int RTWN_VAP_ID_INVALID ; 

__attribute__((used)) static void
rtwn_vap_decrement_counters(struct rtwn_softc *sc,
    enum ieee80211_opmode opmode, int id)
{

	RTWN_ASSERT_LOCKED(sc);

	if (id != RTWN_VAP_ID_INVALID) {
		KASSERT(id == 0 || id == 1, ("wrong vap id %d!\n", id));
		KASSERT(sc->vaps[id] != NULL, ("vap pointer is NULL\n"));
		sc->vaps[id] = NULL;
	}

	switch (opmode) {
	case IEEE80211_M_HOSTAP:
		sc->ap_vaps--;
		/* FALLTHROUGH */
	case IEEE80211_M_IBSS:
		sc->bcn_vaps--;
		/* FALLTHROUGH */
	case IEEE80211_M_STA:
		sc->nvaps--;
		break;
	case IEEE80211_M_MONITOR:
		sc->mon_vaps--;
		break;
	default:
		KASSERT(0, ("wrong opmode %d\n", opmode));
		break;
	}

	KASSERT(sc->vaps_running >= 0 && sc->monvaps_running >= 0,
	    ("number of running vaps is negative (vaps %d, monvaps %d)\n",
	    sc->vaps_running, sc->monvaps_running));
	KASSERT(sc->vaps_running - sc->monvaps_running <= RTWN_PORT_COUNT,
	    ("number of running vaps is too big (vaps %d, monvaps %d)\n",
	    sc->vaps_running, sc->monvaps_running));

	KASSERT(sc->nvaps >= 0 && sc->nvaps <= RTWN_PORT_COUNT,
	    ("wrong value %d for nvaps\n", sc->nvaps));
	KASSERT(sc->mon_vaps >= 0, ("mon_vaps is negative (%d)\n",
	    sc->mon_vaps));
	KASSERT(sc->bcn_vaps >= 0 && ((RTWN_CHIP_HAS_BCNQ1(sc) &&
	    sc->bcn_vaps <= RTWN_PORT_COUNT) || sc->bcn_vaps <= 1),
	    ("bcn_vaps value %d is wrong\n", sc->bcn_vaps));
	KASSERT(sc->ap_vaps >= 0 && ((RTWN_CHIP_HAS_BCNQ1(sc) &&
	    sc->ap_vaps <= RTWN_PORT_COUNT) || sc->ap_vaps <= 1),
	    ("ap_vaps value %d is wrong\n", sc->ap_vaps));
}