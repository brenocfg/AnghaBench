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
struct uath_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct uath_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int UATH_FLAG_INITDONE ; 
 int /*<<< orphan*/  UATH_LOCK (struct uath_softc*) ; 
 int /*<<< orphan*/  UATH_UNLOCK (struct uath_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  uath_start (struct uath_softc*) ; 

__attribute__((used)) static int
uath_transmit(struct ieee80211com *ic, struct mbuf *m)   
{
	struct uath_softc *sc = ic->ic_softc;
	int error;

	UATH_LOCK(sc);
	if ((sc->sc_flags & UATH_FLAG_INITDONE) == 0) {
		UATH_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		UATH_UNLOCK(sc);
		return (error);
	}
	uath_start(sc);
	UATH_UNLOCK(sc);

	return (0);
}