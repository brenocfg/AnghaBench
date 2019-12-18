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
struct sbni_softc {int /*<<< orphan*/  ifp; int /*<<< orphan*/  lock; scalar_t__ irq_handle; int /*<<< orphan*/  irq_res; int /*<<< orphan*/  dev; int /*<<< orphan*/  wch; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBNI_LOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  SBNI_UNLOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbni_stop (struct sbni_softc*) ; 

void
sbni_detach(struct sbni_softc *sc)
{

	SBNI_LOCK(sc);
	sbni_stop(sc);
	SBNI_UNLOCK(sc);
	callout_drain(&sc->wch);
	ether_ifdetach(sc->ifp);
	if (sc->irq_handle)
		bus_teardown_intr(sc->dev, sc->irq_res, sc->irq_handle);
	mtx_destroy(&sc->lock);
	if_free(sc->ifp);
}