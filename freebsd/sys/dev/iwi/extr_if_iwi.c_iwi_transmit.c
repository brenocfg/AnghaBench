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
struct iwi_softc {int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_running; } ;
struct ieee80211com {struct iwi_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  IWI_LOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  IWI_LOCK_DECL ; 
 int /*<<< orphan*/  IWI_UNLOCK (struct iwi_softc*) ; 
 int /*<<< orphan*/  iwi_start (struct iwi_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static int
iwi_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct iwi_softc *sc = ic->ic_softc;
	int error;
	IWI_LOCK_DECL;

	IWI_LOCK(sc);
	if (!sc->sc_running) {
		IWI_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		IWI_UNLOCK(sc);
		return (error);
	}
	iwi_start(sc);
	IWI_UNLOCK(sc);
	return (0);
}