#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lance_softc {int /*<<< orphan*/  sc_mem; } ;
struct TYPE_2__ {struct lance_softc lsc; } ;
struct le_dma_softc {int /*<<< orphan*/  sc_rres; int /*<<< orphan*/  sc_ires; int /*<<< orphan*/  sc_dma; int /*<<< orphan*/  sc_dmat; int /*<<< orphan*/  sc_dmam; TYPE_1__ sc_am7990; int /*<<< orphan*/  sc_ih; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  LE_LOCK_DESTROY (struct lance_softc*) ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  am7990_detach (TYPE_1__*) ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct le_dma_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int lsi64854_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
le_dma_detach(device_t dev)
{
	struct le_dma_softc *lesc;
	struct lance_softc *sc;
	int error;

	lesc = device_get_softc(dev);
	sc = &lesc->sc_am7990.lsc;

	bus_teardown_intr(dev, lesc->sc_ires, lesc->sc_ih);
	am7990_detach(&lesc->sc_am7990);
	bus_dmamap_unload(lesc->sc_dmat, lesc->sc_dmam);
	bus_dmamem_free(lesc->sc_dmat, sc->sc_mem, lesc->sc_dmam);
	bus_dma_tag_destroy(lesc->sc_dmat);
	error = lsi64854_detach(lesc->sc_dma);
	if (error != 0)
		return (error);
	bus_release_resource(dev, SYS_RES_IRQ, rman_get_rid(lesc->sc_ires),
	    lesc->sc_ires);
	bus_release_resource(dev, SYS_RES_MEMORY, rman_get_rid(lesc->sc_rres),
	    lesc->sc_rres);
	LE_LOCK_DESTROY(sc);

	return (0);
}