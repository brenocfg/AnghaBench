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
struct urtw_softc {int sc_flags; } ;
struct ieee80211com {struct urtw_softc* ic_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 int URTW_RUNNING ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 int /*<<< orphan*/  urtw_rx_setconf (struct urtw_softc*) ; 

__attribute__((used)) static void
urtw_update_promisc(struct ieee80211com *ic)
{
	struct urtw_softc *sc = ic->ic_softc;

	URTW_LOCK(sc);
	if (sc->sc_flags & URTW_RUNNING)
		urtw_rx_setconf(sc);
	URTW_UNLOCK(sc);
}