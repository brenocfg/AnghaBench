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
struct malo_softc {int /*<<< orphan*/  malo_snd; int /*<<< orphan*/  malo_running; } ;
struct ieee80211com {struct malo_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  MALO_LOCK (struct malo_softc*) ; 
 int /*<<< orphan*/  MALO_UNLOCK (struct malo_softc*) ; 
 int /*<<< orphan*/  malo_start (struct malo_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static int
malo_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct malo_softc *sc = ic->ic_softc;
	int error;

	MALO_LOCK(sc);
	if (!sc->malo_running) {
		MALO_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->malo_snd, m);
	if (error) {
		MALO_UNLOCK(sc);
		return (error);
	}
	malo_start(sc);
	MALO_UNLOCK(sc);
	return (0);
}