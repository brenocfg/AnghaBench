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
struct ural_softc {int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_running; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct ural_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RAL_LOCK (struct ural_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct ural_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  ural_start (struct ural_softc*) ; 

__attribute__((used)) static int
ural_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct ural_softc *sc = ic->ic_softc;
	int error;

	RAL_LOCK(sc);
	if (!sc->sc_running) {
		RAL_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		RAL_UNLOCK(sc);
		return (error);
	}
	ural_start(sc);
	RAL_UNLOCK(sc);

	return (0);
}