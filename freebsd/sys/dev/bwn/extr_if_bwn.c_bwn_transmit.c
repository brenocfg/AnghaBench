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
struct ieee80211com {struct bwn_softc* ic_softc; } ;
struct bwn_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;

/* Variables and functions */
 int BWN_FLAG_RUNNING ; 
 int /*<<< orphan*/  BWN_LOCK (struct bwn_softc*) ; 
 int /*<<< orphan*/  BWN_UNLOCK (struct bwn_softc*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  bwn_start (struct bwn_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static int
bwn_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct bwn_softc *sc = ic->ic_softc;
	int error;

	BWN_LOCK(sc);
	if ((sc->sc_flags & BWN_FLAG_RUNNING) == 0) {
		BWN_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		BWN_UNLOCK(sc);
		return (error);
	}
	bwn_start(sc);
	BWN_UNLOCK(sc);
	return (0);
}