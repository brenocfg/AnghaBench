#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int dying; int /*<<< orphan*/  parent_dmat; TYPE_9__* ifp; int /*<<< orphan*/  driver_mtx; int /*<<< orphan*/  cmd_mtx; int /*<<< orphan*/  mem_res; int /*<<< orphan*/  cmd_dma; int /*<<< orphan*/  zeropad_dma; int /*<<< orphan*/  dmabench_dma; int /*<<< orphan*/  media; int /*<<< orphan*/  co_hdl; int /*<<< orphan*/ * tq; int /*<<< orphan*/  watchdog_task; int /*<<< orphan*/  dev; } ;
typedef  TYPE_1__ mxge_softc_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_13__ {int if_drv_flags; } ;

/* Variables and functions */
 int EBUSY ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  PCIR_BARS ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 TYPE_1__* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ether_ifdetach (TYPE_9__*) ; 
 int /*<<< orphan*/  if_free (TYPE_9__*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxge_close (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxge_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mxge_dummy_rdma (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mxge_free_rings (TYPE_1__*) ; 
 int /*<<< orphan*/  mxge_free_slices (TYPE_1__*) ; 
 int /*<<< orphan*/  mxge_rem_irq (TYPE_1__*) ; 
 int /*<<< orphan*/  mxge_rem_sysctls (TYPE_1__*) ; 
 scalar_t__ mxge_vlans_active (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_busmaster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mxge_detach(device_t dev)
{
	mxge_softc_t *sc = device_get_softc(dev);

	if (mxge_vlans_active(sc)) {
		device_printf(sc->dev,
			      "Detach vlans before removing module\n");
		return EBUSY;
	}
	mtx_lock(&sc->driver_mtx);
	sc->dying = 1;
	if (sc->ifp->if_drv_flags & IFF_DRV_RUNNING)
		mxge_close(sc, 0);
	mtx_unlock(&sc->driver_mtx);
	ether_ifdetach(sc->ifp);
	if (sc->tq != NULL) {
		taskqueue_drain(sc->tq, &sc->watchdog_task);
		taskqueue_free(sc->tq);
		sc->tq = NULL;
	}
	callout_drain(&sc->co_hdl);
	ifmedia_removeall(&sc->media);
	mxge_dummy_rdma(sc, 0);
	mxge_rem_sysctls(sc);
	mxge_rem_irq(sc);
	mxge_free_rings(sc);
	mxge_free_slices(sc);
	mxge_dma_free(&sc->dmabench_dma);
	mxge_dma_free(&sc->zeropad_dma);
	mxge_dma_free(&sc->cmd_dma);
	bus_release_resource(dev, SYS_RES_MEMORY, PCIR_BARS, sc->mem_res);
	pci_disable_busmaster(dev);
	mtx_destroy(&sc->cmd_mtx);
	mtx_destroy(&sc->driver_mtx);
	if_free(sc->ifp);
	bus_dma_tag_destroy(sc->parent_dmat);
	return 0;
}