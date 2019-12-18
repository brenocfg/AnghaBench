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
struct ndis_softc {scalar_t__ ndis_iftype; int /*<<< orphan*/  ndis_parent_tag; int /*<<< orphan*/ * ndis_txpool; int /*<<< orphan*/  ifmedia; scalar_t__ ndis_80211; scalar_t__ ndis_txarray; scalar_t__ ndis_sc; scalar_t__ ndis_res_altmem; int /*<<< orphan*/  ndis_altmem_rid; scalar_t__ ndis_res_mem; int /*<<< orphan*/  ndis_mem_rid; scalar_t__ ndis_res_io; int /*<<< orphan*/  ndis_io_rid; scalar_t__ ndis_irq; int /*<<< orphan*/ * ndisusb_taskitem; int /*<<< orphan*/ * ndisusb_xferdoneitem; int /*<<< orphan*/ * ndis_inputitem; int /*<<< orphan*/ * ndis_resetitem; int /*<<< orphan*/ * ndis_startitem; int /*<<< orphan*/ * ndis_tickitem; int /*<<< orphan*/  ndis_ic; struct ifnet* ifp; } ;
struct ifnet {int /*<<< orphan*/  if_flags; } ;
typedef  int /*<<< orphan*/  driver_object ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  IoFreeWorkItem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  NDIS_LOCK (struct ndis_softc*) ; 
 int /*<<< orphan*/  NDIS_UNLOCK (struct ndis_softc*) ; 
 int /*<<< orphan*/  NdisFreePacketPool (int /*<<< orphan*/ *) ; 
 scalar_t__ PCIBus ; 
 scalar_t__ PCMCIABus ; 
 int /*<<< orphan*/  SYS_RES_IOPORT ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 struct ndis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  free (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ndis_destroy_dma (struct ndis_softc*) ; 
 int /*<<< orphan*/  ndis_stop (struct ndis_softc*) ; 
 int /*<<< orphan*/  ndis_unload_driver (struct ndis_softc*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  windrv_destroy_pdo (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * windrv_lookup (int /*<<< orphan*/ ,char*) ; 

int
ndis_detach(device_t dev)
{
	struct ifnet		*ifp;
	struct ndis_softc	*sc;
	driver_object		*drv;

	sc = device_get_softc(dev);
	NDIS_LOCK(sc);
	if (!sc->ndis_80211)
		ifp = sc->ifp;
	else
		ifp = NULL;
	if (ifp != NULL)
		ifp->if_flags &= ~IFF_UP;
	if (device_is_attached(dev)) {
		NDIS_UNLOCK(sc);
		ndis_stop(sc);
		if (sc->ndis_80211)
			ieee80211_ifdetach(&sc->ndis_ic);
		else if (ifp != NULL)
			ether_ifdetach(ifp);
	} else
		NDIS_UNLOCK(sc);

	if (sc->ndis_tickitem != NULL)
		IoFreeWorkItem(sc->ndis_tickitem);
	if (sc->ndis_startitem != NULL)
		IoFreeWorkItem(sc->ndis_startitem);
	if (sc->ndis_resetitem != NULL)
		IoFreeWorkItem(sc->ndis_resetitem);
	if (sc->ndis_inputitem != NULL)
		IoFreeWorkItem(sc->ndis_inputitem);
	if (sc->ndisusb_xferdoneitem != NULL)
		IoFreeWorkItem(sc->ndisusb_xferdoneitem);
	if (sc->ndisusb_taskitem != NULL)
		IoFreeWorkItem(sc->ndisusb_taskitem);

	bus_generic_detach(dev);
	ndis_unload_driver(sc);

	if (sc->ndis_irq)
		bus_release_resource(dev, SYS_RES_IRQ, 0, sc->ndis_irq);
	if (sc->ndis_res_io)
		bus_release_resource(dev, SYS_RES_IOPORT,
		    sc->ndis_io_rid, sc->ndis_res_io);
	if (sc->ndis_res_mem)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->ndis_mem_rid, sc->ndis_res_mem);
	if (sc->ndis_res_altmem)
		bus_release_resource(dev, SYS_RES_MEMORY,
		    sc->ndis_altmem_rid, sc->ndis_res_altmem);

	if (ifp != NULL)
		if_free(ifp);

	if (sc->ndis_sc)
		ndis_destroy_dma(sc);

	if (sc->ndis_txarray)
		free(sc->ndis_txarray, M_DEVBUF);

	if (!sc->ndis_80211)
		ifmedia_removeall(&sc->ifmedia);

	if (sc->ndis_txpool != NULL)
		NdisFreePacketPool(sc->ndis_txpool);

	/* Destroy the PDO for this device. */
	
	if (sc->ndis_iftype == PCIBus)
		drv = windrv_lookup(0, "PCI Bus");
	else if (sc->ndis_iftype == PCMCIABus)
		drv = windrv_lookup(0, "PCCARD Bus");
	else
		drv = windrv_lookup(0, "USB Bus");
	if (drv == NULL)
		panic("couldn't find driver object");
	windrv_destroy_pdo(drv, dev);

	if (sc->ndis_iftype == PCIBus)
		bus_dma_tag_destroy(sc->ndis_parent_tag);

	return (0);
}