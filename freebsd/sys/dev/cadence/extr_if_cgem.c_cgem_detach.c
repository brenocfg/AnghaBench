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
struct cgem_softc {scalar_t__ rxring_physaddr; scalar_t__ txring_physaddr; int /*<<< orphan*/ * mbuf_dma_tag; int /*<<< orphan*/ * desc_dma_tag; int /*<<< orphan*/ ** txring_m_dmamap; int /*<<< orphan*/ * txring; int /*<<< orphan*/  txring_dma_map; int /*<<< orphan*/ ** rxring_m_dmamap; int /*<<< orphan*/ * rxring; int /*<<< orphan*/  rxring_dma_map; int /*<<< orphan*/ * irq_res; scalar_t__ intrhand; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * miibus; int /*<<< orphan*/  ifp; int /*<<< orphan*/  tick_ch; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CGEM_LOCK (struct cgem_softc*) ; 
 int /*<<< orphan*/  CGEM_LOCK_DESTROY (struct cgem_softc*) ; 
 int CGEM_NUM_RX_DESCS ; 
 int CGEM_NUM_TX_DESCS ; 
 int /*<<< orphan*/  CGEM_UNLOCK (struct cgem_softc*) ; 
 int ENODEV ; 
 int /*<<< orphan*/  IFF_UP ; 
 int /*<<< orphan*/  SYS_RES_IRQ ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgem_stop (struct cgem_softc*) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct cgem_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  if_setflagbits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_rid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
cgem_detach(device_t dev)
{
	struct cgem_softc *sc = device_get_softc(dev);
	int i;

	if (sc == NULL)
		return (ENODEV);

	if (device_is_attached(dev)) {
		CGEM_LOCK(sc);
		cgem_stop(sc);
		CGEM_UNLOCK(sc);
		callout_drain(&sc->tick_ch);
		if_setflagbits(sc->ifp, 0, IFF_UP);
		ether_ifdetach(sc->ifp);
	}

	if (sc->miibus != NULL) {
		device_delete_child(dev, sc->miibus);
		sc->miibus = NULL;
	}

	/* Release resources. */
	if (sc->mem_res != NULL) {
		bus_release_resource(dev, SYS_RES_MEMORY,
				     rman_get_rid(sc->mem_res), sc->mem_res);
		sc->mem_res = NULL;
	}
	if (sc->irq_res != NULL) {
		if (sc->intrhand)
			bus_teardown_intr(dev, sc->irq_res, sc->intrhand);
		bus_release_resource(dev, SYS_RES_IRQ,
				     rman_get_rid(sc->irq_res), sc->irq_res);
		sc->irq_res = NULL;
	}

	/* Release DMA resources. */
	if (sc->rxring != NULL) {
		if (sc->rxring_physaddr != 0) {
			bus_dmamap_unload(sc->desc_dma_tag,
					  sc->rxring_dma_map);
			sc->rxring_physaddr = 0;
		}
		bus_dmamem_free(sc->desc_dma_tag, sc->rxring,
				sc->rxring_dma_map);
		sc->rxring = NULL;
		for (i = 0; i < CGEM_NUM_RX_DESCS; i++)
			if (sc->rxring_m_dmamap[i] != NULL) {
				bus_dmamap_destroy(sc->mbuf_dma_tag,
						   sc->rxring_m_dmamap[i]);
				sc->rxring_m_dmamap[i] = NULL;
			}
	}
	if (sc->txring != NULL) {
		if (sc->txring_physaddr != 0) {
			bus_dmamap_unload(sc->desc_dma_tag,
					  sc->txring_dma_map);
			sc->txring_physaddr = 0;
		}
		bus_dmamem_free(sc->desc_dma_tag, sc->txring,
				sc->txring_dma_map);
		sc->txring = NULL;
		for (i = 0; i < CGEM_NUM_TX_DESCS; i++)
			if (sc->txring_m_dmamap[i] != NULL) {
				bus_dmamap_destroy(sc->mbuf_dma_tag,
						   sc->txring_m_dmamap[i]);
				sc->txring_m_dmamap[i] = NULL;
			}
	}
	if (sc->desc_dma_tag != NULL) {
		bus_dma_tag_destroy(sc->desc_dma_tag);
		sc->desc_dma_tag = NULL;
	}
	if (sc->mbuf_dma_tag != NULL) {
		bus_dma_tag_destroy(sc->mbuf_dma_tag);
		sc->mbuf_dma_tag = NULL;
	}

	bus_generic_detach(dev);

	CGEM_LOCK_DESTROY(sc);

	return (0);
}