#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct otus_softc {int dummy; } ;
struct TYPE_2__ {scalar_t__ ic_allmulti; scalar_t__ ic_promisc; scalar_t__ ic_opmode; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR_MAC_REG_FRAMETYPE_FILTER ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  OTUS_LOCK_ASSERT (struct otus_softc*) ; 
 TYPE_1__* ic ; 
 int /*<<< orphan*/  otus_write (struct otus_softc*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
otus_set_rx_filter(struct otus_softc *sc)
{
//	struct ieee80211com *ic = &sc->sc_ic;

	OTUS_LOCK_ASSERT(sc);

#if 0
	if (ic->ic_allmulti > 0 || ic->ic_promisc > 0 ||
	    ic->ic_opmode == IEEE80211_M_MONITOR) {
		otus_write(sc, AR_MAC_REG_FRAMETYPE_FILTER, 0xff00ffff);
	} else {
#endif
		/* Filter any control frames, BAR is bit 24. */
		otus_write(sc, AR_MAC_REG_FRAMETYPE_FILTER, 0x0500ffff);
#if 0
	}
#endif
}