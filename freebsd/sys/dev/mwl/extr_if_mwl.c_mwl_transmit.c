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
struct mwl_softc {int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_running; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct mwl_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MWL_LOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_UNLOCK (struct mwl_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  mwl_start (struct mwl_softc*) ; 

__attribute__((used)) static int
mwl_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct mwl_softc *sc = ic->ic_softc;
	int error;

	MWL_LOCK(sc);
	if (!sc->sc_running) {
		MWL_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		MWL_UNLOCK(sc);
		return (error);
	}
	mwl_start(sc);
	MWL_UNLOCK(sc);
	return (0);
}