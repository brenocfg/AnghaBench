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
struct bge_softc {int /*<<< orphan*/  bge_mtx; int /*<<< orphan*/ * bge_ifp; int /*<<< orphan*/ * bge_res2; int /*<<< orphan*/ * bge_res; int /*<<< orphan*/ * bge_irq; int /*<<< orphan*/ * bge_intrhand; int /*<<< orphan*/ * bge_tq; int /*<<< orphan*/  bge_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  BGE_LOCK_DESTROY (struct bge_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bge_dma_free (struct bge_softc*) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_release_msi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bge_release_resources(struct bge_softc *sc)
{
	device_t dev;

	dev = sc->bge_dev;

	if (sc->bge_tq != NULL)
		taskqueue_free(sc->bge_tq);

	if (sc->bge_intrhand != NULL)
		bus_teardown_intr(dev, sc->bge_irq, sc->bge_intrhand);

	if (sc->bge_irq != NULL) {
		bus_release_resource(dev, SYS_RES_IRQ,
		    rman_get_rid(sc->bge_irq), sc->bge_irq);
		pci_release_msi(dev);
	}

	if (sc->bge_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->bge_res), sc->bge_res);

	if (sc->bge_res2 != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    rman_get_rid(sc->bge_res2), sc->bge_res2);

	if (sc->bge_ifp != NULL)
		if_free(sc->bge_ifp);

	bge_dma_free(sc);

	if (mtx_initialized(&sc->bge_mtx))	/* XXX */
		BGE_LOCK_DESTROY(sc);
}