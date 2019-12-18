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
struct wi_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct wi_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int WI_FLAGS_RUNNING ; 
 int /*<<< orphan*/  WI_LOCK (struct wi_softc*) ; 
 int /*<<< orphan*/  WI_UNLOCK (struct wi_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  wi_start (struct wi_softc*) ; 

__attribute__((used)) static int
wi_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct wi_softc *sc = ic->ic_softc;
	int error;

	WI_LOCK(sc);
	if ((sc->sc_flags & WI_FLAGS_RUNNING) == 0) {
		WI_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		WI_UNLOCK(sc);
		return (error);
	}
	wi_start(sc);
	WI_UNLOCK(sc);
	return (0);
}