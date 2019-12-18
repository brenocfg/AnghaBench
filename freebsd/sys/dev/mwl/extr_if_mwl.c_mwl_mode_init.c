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
struct ieee80211com {scalar_t__ ic_promisc; } ;
struct mwl_softc {struct mwl_hal* sc_mh; struct ieee80211com sc_ic; } ;
struct mwl_hal {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mwl_hal_setpromisc (struct mwl_hal*,int) ; 
 int /*<<< orphan*/  mwl_setmcastfilter (struct mwl_softc*) ; 

__attribute__((used)) static int
mwl_mode_init(struct mwl_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct mwl_hal *mh = sc->sc_mh;

	mwl_hal_setpromisc(mh, ic->ic_promisc > 0);
	mwl_setmcastfilter(sc);

	return 0;
}