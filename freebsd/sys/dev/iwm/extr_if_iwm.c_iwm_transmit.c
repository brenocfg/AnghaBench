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
struct mbuf {int dummy; } ;
struct iwm_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct ieee80211com {struct iwm_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int IWM_FLAG_HW_INITED ; 
 int /*<<< orphan*/  IWM_LOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  IWM_UNLOCK (struct iwm_softc*) ; 
 int /*<<< orphan*/  iwm_start (struct iwm_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static int
iwm_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct iwm_softc *sc;
	int error;

	sc = ic->ic_softc;

	IWM_LOCK(sc);
	if ((sc->sc_flags & IWM_FLAG_HW_INITED) == 0) {
		IWM_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		IWM_UNLOCK(sc);
		return (error);
	}
	iwm_start(sc);
	IWM_UNLOCK(sc);
	return (0);
}