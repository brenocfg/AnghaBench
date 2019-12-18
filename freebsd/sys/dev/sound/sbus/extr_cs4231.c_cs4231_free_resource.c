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
struct cs4231_softc {int sc_nires; int sc_nmres; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/ ** sc_res; int /*<<< orphan*/ * sc_rid; int /*<<< orphan*/  sc_dev; scalar_t__* sc_dmat; int /*<<< orphan*/ ** sc_irqres; int /*<<< orphan*/ * sc_irqrid; int /*<<< orphan*/ ** sc_ih; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS4231_LOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  CS4231_UNLOCK (struct cs4231_softc*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (scalar_t__) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cs4231_disable (struct cs4231_softc*) ; 
 int /*<<< orphan*/  free (struct cs4231_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_mtxfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cs4231_free_resource(struct cs4231_softc *sc)
{
	int i;

	CS4231_LOCK(sc);
	cs4231_disable(sc);
	CS4231_UNLOCK(sc);
	for (i = 0; i < sc->sc_nires; i++) {
		if (sc->sc_irqres[i]) {
			if (sc->sc_ih[i]) {
				bus_teardown_intr(sc->sc_dev, sc->sc_irqres[i],
				    sc->sc_ih[i]);
				sc->sc_ih[i] = NULL;
			}
			bus_release_resource(sc->sc_dev, SYS_RES_IRQ,
			    sc->sc_irqrid[i], sc->sc_irqres[i]);
			sc->sc_irqres[i] = NULL;
		}
	}
	for (i = 0; i < sc->sc_nires; i++) {
		if (sc->sc_dmat[i])
			bus_dma_tag_destroy(sc->sc_dmat[i]);
	}
	for (i = 0; i < sc->sc_nmres; i++) {
		if (sc->sc_res[i])
			bus_release_resource(sc->sc_dev, SYS_RES_MEMORY,
			    sc->sc_rid[i], sc->sc_res[i]);
	}
	snd_mtxfree(sc->sc_lock);
	free(sc, M_DEVBUF);
}