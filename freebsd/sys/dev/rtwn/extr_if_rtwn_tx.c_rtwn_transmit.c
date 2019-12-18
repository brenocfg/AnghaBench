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
struct rtwn_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct rtwn_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RTWN_LOCK (struct rtwn_softc*) ; 
 int RTWN_RUNNING ; 
 int /*<<< orphan*/  RTWN_UNLOCK (struct rtwn_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  rtwn_start (struct rtwn_softc*) ; 

int
rtwn_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct rtwn_softc *sc = ic->ic_softc;
	int error;

	RTWN_LOCK(sc);
	if ((sc->sc_flags & RTWN_RUNNING) == 0) {
		RTWN_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		RTWN_UNLOCK(sc);
		return (error);
	}
	rtwn_start(sc);
	RTWN_UNLOCK(sc);

	return (0);
}