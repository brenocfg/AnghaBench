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
struct run_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct run_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RUN_LOCK (struct run_softc*) ; 
 int RUN_RUNNING ; 
 int /*<<< orphan*/  RUN_UNLOCK (struct run_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  run_start (struct run_softc*) ; 

__attribute__((used)) static int
run_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct run_softc *sc = ic->ic_softc;
	int error;

	RUN_LOCK(sc);
	if ((sc->sc_flags & RUN_RUNNING) == 0) {
		RUN_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		RUN_UNLOCK(sc);
		return (error);
	}
	run_start(sc);
	RUN_UNLOCK(sc);

	return (0);
}