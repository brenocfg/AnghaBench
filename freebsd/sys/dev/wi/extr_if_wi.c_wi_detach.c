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
struct ieee80211com {int dummy; } ;
struct wi_softc {int wi_gone; int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  wi_intrhand; int /*<<< orphan*/  irq; struct ieee80211com sc_ic; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  WI_LOCK (struct wi_softc*) ; 
 int /*<<< orphan*/  WI_UNLOCK (struct wi_softc*) ; 
 int /*<<< orphan*/  bus_child_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wi_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wi_stop (struct wi_softc*,int /*<<< orphan*/ ) ; 

int
wi_detach(device_t dev)
{
	struct wi_softc	*sc = device_get_softc(dev);
	struct ieee80211com *ic = &sc->sc_ic;

	WI_LOCK(sc);

	/* check if device was removed */
	sc->wi_gone |= !bus_child_present(dev);

	wi_stop(sc, 0);
	WI_UNLOCK(sc);
	ieee80211_ifdetach(ic);

	bus_teardown_intr(dev, sc->irq, sc->wi_intrhand);
	wi_free(dev);
	mbufq_drain(&sc->sc_snd);
	mtx_destroy(&sc->sc_mtx);
	return (0);
}