#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  callout; } ;
struct cpsw_softc {TYPE_4__ tx; TYPE_3__ rx; int /*<<< orphan*/  irq_res; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/  mem_rid; scalar_t__ mbuf_dtag; scalar_t__ nullpad; int /*<<< orphan*/ * _slots; TYPE_2__ watchdog; TYPE_1__* port; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_5__ {scalar_t__ dev; } ;

/* Variables and functions */
 int CPSW_PORTS ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int bus_dma_tag_destroy (scalar_t__) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_free_slot (struct cpsw_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cpsw_intr_detach (struct cpsw_softc*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 int device_delete_children (int /*<<< orphan*/ ) ; 
 struct cpsw_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_res_spec ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int nitems (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cpsw_detach(device_t dev)
{
	struct cpsw_softc *sc;
	int error, i;

	bus_generic_detach(dev);
 	sc = device_get_softc(dev);

	for (i = 0; i < CPSW_PORTS; i++) {
		if (sc->port[i].dev)
			device_delete_child(dev, sc->port[i].dev);
	}

	if (device_is_attached(dev)) {
		callout_stop(&sc->watchdog.callout);
		callout_drain(&sc->watchdog.callout);
	}

	/* Stop and release all interrupts */
	cpsw_intr_detach(sc);

	/* Free dmamaps and mbufs */
	for (i = 0; i < nitems(sc->_slots); ++i)
		cpsw_free_slot(sc, &sc->_slots[i]);

	/* Free null padding buffer. */
	if (sc->nullpad)
		free(sc->nullpad, M_DEVBUF);

	/* Free DMA tag */
	if (sc->mbuf_dtag) {
		error = bus_dma_tag_destroy(sc->mbuf_dtag);
		KASSERT(error == 0, ("Unable to destroy DMA tag"));
	}

	/* Free IO memory handler */
	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, sc->mem_rid, sc->mem_res);
	bus_release_resources(dev, irq_res_spec, sc->irq_res);

	/* Destroy mutexes */
	mtx_destroy(&sc->rx.lock);
	mtx_destroy(&sc->tx.lock);

	/* Detach the switch device, if present. */
	error = bus_generic_detach(dev);
	if (error != 0)
		return (error);
        
	return (device_delete_children(dev));
}