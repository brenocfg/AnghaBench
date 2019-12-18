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
struct rt2661_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct rt2661_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RAL_LOCK (struct rt2661_softc*) ; 
 int RAL_RUNNING ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2661_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  rt2661_start (struct rt2661_softc*) ; 

__attribute__((used)) static int
rt2661_transmit(struct ieee80211com *ic, struct mbuf *m)   
{
	struct rt2661_softc *sc = ic->ic_softc;
	int error;

	RAL_LOCK(sc);
	if ((sc->sc_flags & RAL_RUNNING) == 0) {
		RAL_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		RAL_UNLOCK(sc);
		return (error);
	}
	rt2661_start(sc);
	RAL_UNLOCK(sc);

	return (0);
}