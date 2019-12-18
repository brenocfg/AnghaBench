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
struct zyd_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct zyd_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int ZYD_FLAG_RUNNING ; 
 int /*<<< orphan*/  ZYD_LOCK (struct zyd_softc*) ; 
 int /*<<< orphan*/  ZYD_UNLOCK (struct zyd_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  zyd_start (struct zyd_softc*) ; 

__attribute__((used)) static int
zyd_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct zyd_softc *sc = ic->ic_softc;
	int error;

	ZYD_LOCK(sc);
	if ((sc->sc_flags & ZYD_FLAG_RUNNING) == 0) {
		ZYD_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		ZYD_UNLOCK(sc);
		return (error);
	}
	zyd_start(sc);
	ZYD_UNLOCK(sc);

	return (0);
}