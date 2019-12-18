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
struct upgt_softc {int sc_flags; scalar_t__ sc_tx_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IEEE80211_S_INIT ; 
 int /*<<< orphan*/  UPGT_ASSERT_LOCKED (struct upgt_softc*) ; 
 int UPGT_FLAG_INITDONE ; 
 int /*<<< orphan*/  upgt_abort_xfers_locked (struct upgt_softc*) ; 
 int /*<<< orphan*/  upgt_set_macfilter (struct upgt_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
upgt_stop(struct upgt_softc *sc)
{

	UPGT_ASSERT_LOCKED(sc);

	if (sc->sc_flags & UPGT_FLAG_INITDONE)
		upgt_set_macfilter(sc, IEEE80211_S_INIT);
	upgt_abort_xfers_locked(sc);
	/* device down */
	sc->sc_tx_timer = 0;
	sc->sc_flags &= ~UPGT_FLAG_INITDONE;
}