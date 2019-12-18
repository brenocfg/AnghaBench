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
struct TYPE_2__ {scalar_t__ ic_nrunning; } ;
struct mwl_softc {TYPE_1__ sc_ic; } ;

/* Variables and functions */
 int EDOOFUS ; 
 int /*<<< orphan*/  MWL_LOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_UNLOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  ieee80211_start_all (TYPE_1__*) ; 
 int mwl_init (struct mwl_softc*) ; 

void
mwl_resume(struct mwl_softc *sc)
{
	int error = EDOOFUS;

	MWL_LOCK(sc);
	if (sc->sc_ic.ic_nrunning > 0)
		error = mwl_init(sc);
	MWL_UNLOCK(sc);

	if (error == 0)
		ieee80211_start_all(&sc->sc_ic);	/* start all vap's */
}