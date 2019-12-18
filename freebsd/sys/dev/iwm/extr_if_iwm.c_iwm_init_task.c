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
struct iwm_softc {int sc_flags; TYPE_1__ sc_ic; int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int IWM_FLAG_BUSY ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_init (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_stop (struct iwm_softc*) ; 
 int /*<<< orphan*/  msleep (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (int*) ; 

void
iwm_init_task(void *arg1)
{
	struct iwm_softc *sc = arg1;

	IWM_LOCK(sc);
	while (sc->sc_flags & IWM_FLAG_BUSY)
		msleep(&sc->sc_flags, &sc->sc_mtx, 0, "iwmpwr", 0);
	sc->sc_flags |= IWM_FLAG_BUSY;
	iwm_stop(sc);
	if (sc->sc_ic.ic_nrunning > 0)
		iwm_init(sc);
	sc->sc_flags &= ~IWM_FLAG_BUSY;
	wakeup(&sc->sc_flags);
	IWM_UNLOCK(sc);
}