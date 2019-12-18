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
struct upgt_softc {int sc_flags; int /*<<< orphan*/  sc_snd; } ;
struct mbuf {int dummy; } ;
struct ieee80211com {struct upgt_softc* ic_softc; } ;

/* Variables and functions */
 int ENXIO ; 
 int UPGT_FLAG_INITDONE ; 
 int /*<<< orphan*/  UPGT_LOCK (struct upgt_softc*) ; 
 int /*<<< orphan*/  UPGT_UNLOCK (struct upgt_softc*) ; 
 int mbufq_enqueue (int /*<<< orphan*/ *,struct mbuf*) ; 
 int /*<<< orphan*/  upgt_start (struct upgt_softc*) ; 

__attribute__((used)) static int
upgt_transmit(struct ieee80211com *ic, struct mbuf *m)   
{
	struct upgt_softc *sc = ic->ic_softc;
	int error;

	UPGT_LOCK(sc);
	if ((sc->sc_flags & UPGT_FLAG_INITDONE) == 0) {
		UPGT_UNLOCK(sc);
		return (ENXIO);
	}
	error = mbufq_enqueue(&sc->sc_snd, m);
	if (error) {
		UPGT_UNLOCK(sc);
		return (error);
	}
	upgt_start(sc);
	UPGT_UNLOCK(sc);

	return (0);
}