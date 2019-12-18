#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct smc_softc {int /*<<< orphan*/  smc_mtx; int /*<<< orphan*/ * smc_irq; int /*<<< orphan*/  smc_irq_rid; int /*<<< orphan*/  smc_dev; int /*<<< orphan*/ * smc_reg; int /*<<< orphan*/  smc_reg_rid; scalar_t__ smc_usemem; int /*<<< orphan*/ * smc_miibus; TYPE_1__* smc_ifp; int /*<<< orphan*/ * smc_tq; int /*<<< orphan*/  smc_tx; int /*<<< orphan*/  smc_rx; int /*<<< orphan*/  smc_intr; int /*<<< orphan*/ * smc_ih; int /*<<< orphan*/  smc_mii_tick_ch; int /*<<< orphan*/  smc_watchdog; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {int if_capenable; } ;

/* Variables and functions */
 int IFCAP_POLLING ; 
 int /*<<< orphan*/  SMC_LOCK (struct smc_softc*) ; 
 int /*<<< orphan*/  SMC_UNLOCK (struct smc_softc*) ; 
 int SYS_RES_IOPORT ; 
 int SYS_RES_IRQ ; 
 int SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct smc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (TYPE_1__*) ; 
 int /*<<< orphan*/  ether_poll_deregister (TYPE_1__*) ; 
 int /*<<< orphan*/  if_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_stop (struct smc_softc*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

int
smc_detach(device_t dev)
{
	int			type;
	struct smc_softc	*sc;

	sc = device_get_softc(dev);
	SMC_LOCK(sc);
	smc_stop(sc);
	SMC_UNLOCK(sc);

	if (sc->smc_ifp != NULL) {
		ether_ifdetach(sc->smc_ifp);
	}
	
	callout_drain(&sc->smc_watchdog);
	callout_drain(&sc->smc_mii_tick_ch);
	
#ifdef DEVICE_POLLING
	if (sc->smc_ifp->if_capenable & IFCAP_POLLING)
		ether_poll_deregister(sc->smc_ifp);
#endif

	if (sc->smc_ih != NULL)
		bus_teardown_intr(sc->smc_dev, sc->smc_irq, sc->smc_ih);

	if (sc->smc_tq != NULL) {
		taskqueue_drain(sc->smc_tq, &sc->smc_intr);
		taskqueue_drain(sc->smc_tq, &sc->smc_rx);
		taskqueue_drain(sc->smc_tq, &sc->smc_tx);
		taskqueue_free(sc->smc_tq);
		sc->smc_tq = NULL;
	}

	if (sc->smc_ifp != NULL) {
		if_free(sc->smc_ifp);
	}

	if (sc->smc_miibus != NULL) {
		device_delete_child(sc->smc_dev, sc->smc_miibus);
		bus_generic_detach(sc->smc_dev);
	}

	if (sc->smc_reg != NULL) {
		type = SYS_RES_IOPORT;
		if (sc->smc_usemem)
			type = SYS_RES_MEMORY;

		bus_release_resource(sc->smc_dev, type, sc->smc_reg_rid,
		    sc->smc_reg);
	}

	if (sc->smc_irq != NULL)
		bus_release_resource(sc->smc_dev, SYS_RES_IRQ, sc->smc_irq_rid,
		   sc->smc_irq);

	if (mtx_initialized(&sc->smc_mtx))
		mtx_destroy(&sc->smc_mtx);

	return (0);
}