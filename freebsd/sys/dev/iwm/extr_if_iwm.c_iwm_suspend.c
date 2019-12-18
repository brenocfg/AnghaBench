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
struct iwm_softc {int /*<<< orphan*/  sc_flags; TYPE_1__ sc_ic; int /*<<< orphan*/  sc_attached; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IWM_FLAG_SCANNING ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 struct iwm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_suspend_all (TYPE_1__*) ; 
 int /*<<< orphan*/  iwm_stop (struct iwm_softc*) ; 

__attribute__((used)) static int
iwm_suspend(device_t dev)
{
	int do_stop = 0;
	struct iwm_softc *sc = device_get_softc(dev);

	do_stop = !! (sc->sc_ic.ic_nrunning > 0);

	if (!sc->sc_attached)
		return (0);

	ieee80211_suspend_all(&sc->sc_ic);

	if (do_stop) {
		IWM_LOCK(sc);
		iwm_stop(sc);
		sc->sc_flags |= IWM_FLAG_SCANNING;
		IWM_UNLOCK(sc);
	}

	return (0);
}