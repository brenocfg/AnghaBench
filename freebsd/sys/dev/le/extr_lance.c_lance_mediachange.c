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
struct lance_softc {int /*<<< orphan*/  (* sc_start_locked ) (struct lance_softc*) ;scalar_t__ sc_mediachange; } ;
struct ifnet {int /*<<< orphan*/  if_snd; struct lance_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_DRV_IS_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LE_LOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  LE_UNLOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  lance_init_locked (struct lance_softc*) ; 
 int /*<<< orphan*/  lance_stop (struct lance_softc*) ; 
 int /*<<< orphan*/  stub1 (struct lance_softc*) ; 

__attribute__((used)) static int
lance_mediachange(struct ifnet *ifp)
{
	struct lance_softc *sc = ifp->if_softc;

	if (sc->sc_mediachange) {
		/*
		 * For setting the port in LE_CSR15 the PCnet chips must
		 * be powered down or stopped and unlike documented may
		 * not take effect without an initialization. So don't
		 * invoke (*sc_mediachange) directly here but go through
		 * lance_init_locked().
		 */
		LE_LOCK(sc);
		lance_stop(sc);
		lance_init_locked(sc);
		if (!IFQ_DRV_IS_EMPTY(&ifp->if_snd))
			(*sc->sc_start_locked)(sc);
		LE_UNLOCK(sc);
	}
	return (0);
}