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
struct rum_softc {int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_running; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct rum_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  RUM_LOCK (struct rum_softc*) ; 
 int /*<<< orphan*/  RUM_UNLOCK (struct rum_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  rum_start (struct rum_softc*) ; 

__attribute__((used)) static int
rum_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct rum_softc *sc = ic->ic_softc;
	int error;

	RUM_LOCK(sc);
	if (!sc->sc_running) {
		RUM_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		RUM_UNLOCK(sc);
		return (error);
	}
	rum_start(sc);
	RUM_UNLOCK(sc);

	return (0);
}