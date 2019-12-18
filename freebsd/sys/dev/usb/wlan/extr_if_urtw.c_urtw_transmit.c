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
struct urtw_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct urtw_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  URTW_LOCK (struct urtw_softc*) ; 
 int URTW_RUNNING ; 
 int /*<<< orphan*/  URTW_UNLOCK (struct urtw_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  urtw_start (struct urtw_softc*) ; 

__attribute__((used)) static int
urtw_transmit(struct ieee80211com *ic, struct mbuf *m)   
{
	struct urtw_softc *sc = ic->ic_softc;
	int error;

	URTW_LOCK(sc);
	if ((sc->sc_flags & URTW_RUNNING) == 0) {
		URTW_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		URTW_UNLOCK(sc);
		return (error);
	}
	urtw_start(sc);
	URTW_UNLOCK(sc);

	return (0);
}