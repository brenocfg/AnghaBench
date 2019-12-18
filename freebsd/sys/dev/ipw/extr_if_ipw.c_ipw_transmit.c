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
struct ipw_softc {int flags; int /*<<< orphan*/  sc_snd; } ;
struct ieee80211com {struct ipw_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int IPW_FLAG_RUNNING ; 
 int /*<<< orphan*/  IPW_LOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  IPW_UNLOCK (struct ipw_softc*) ; 
 int /*<<< orphan*/  ipw_start (struct ipw_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 

__attribute__((used)) static int
ipw_transmit(struct ieee80211com *ic, struct mbuf *m)
{
	struct ipw_softc *sc = ic->ic_softc;
	int error;

	IPW_LOCK(sc);
	if ((sc->flags & IPW_FLAG_RUNNING) == 0) {
		IPW_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		IPW_UNLOCK(sc);
		return (error);
	}
	ipw_start(sc);
	IPW_UNLOCK(sc);
	return (0);
}