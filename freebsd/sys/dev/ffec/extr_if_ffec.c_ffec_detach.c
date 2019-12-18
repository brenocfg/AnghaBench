#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ffec_softc {int is_detaching; int /*<<< orphan*/ * mem_res; int /*<<< orphan*/ * irq_res; int /*<<< orphan*/ ** intr_cookie; int /*<<< orphan*/ * txdesc_tag; int /*<<< orphan*/ * txdesc_map; int /*<<< orphan*/ * txbuf_tag; TYPE_2__* txbuf_map; int /*<<< orphan*/ * rxdesc_tag; int /*<<< orphan*/ * rxdesc_map; int /*<<< orphan*/ * rxbuf_tag; TYPE_1__* rxbuf_map; int /*<<< orphan*/  ifp; int /*<<< orphan*/  ffec_callout; scalar_t__ is_attached; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * bus_dmamap_t ;
struct TYPE_4__ {int /*<<< orphan*/ * map; } ;
struct TYPE_3__ {int /*<<< orphan*/  mbuf; int /*<<< orphan*/ * map; } ;

/* Variables and functions */
 int /*<<< orphan*/  FFEC_LOCK (struct ffec_softc*) ; 
 int /*<<< orphan*/  FFEC_LOCK_DESTROY (struct ffec_softc*) ; 
 int /*<<< orphan*/  FFEC_UNLOCK (struct ffec_softc*) ; 
 int MAX_IRQ_COUNT ; 
 int RX_DESC_COUNT ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int TX_DESC_COUNT ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct ffec_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_ifdetach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ffec_stop_locked (struct ffec_softc*) ; 
 int /*<<< orphan*/  irq_res_spec ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ffec_detach(device_t dev)
{
	struct ffec_softc *sc;
	bus_dmamap_t map;
	int idx, irq;

	/*
	 * NB: This function can be called internally to unwind a failure to
	 * attach. Make sure a resource got allocated/created before destroying.
	 */

	sc = device_get_softc(dev);

	if (sc->is_attached) {
		FFEC_LOCK(sc);
		sc->is_detaching = true;
		ffec_stop_locked(sc);
		FFEC_UNLOCK(sc);
		callout_drain(&sc->ffec_callout);
		ether_ifdetach(sc->ifp);
	}

	/* XXX no miibus detach? */

	/* Clean up RX DMA resources and free mbufs. */
	for (idx = 0; idx < RX_DESC_COUNT; ++idx) {
		if ((map = sc->rxbuf_map[idx].map) != NULL) {
			bus_dmamap_unload(sc->rxbuf_tag, map);
			bus_dmamap_destroy(sc->rxbuf_tag, map);
			m_freem(sc->rxbuf_map[idx].mbuf);
		}
	}
	if (sc->rxbuf_tag != NULL)
		bus_dma_tag_destroy(sc->rxbuf_tag);
	if (sc->rxdesc_map != NULL) {
		bus_dmamap_unload(sc->rxdesc_tag, sc->rxdesc_map);
		bus_dmamap_destroy(sc->rxdesc_tag, sc->rxdesc_map);
	}
	if (sc->rxdesc_tag != NULL)
	bus_dma_tag_destroy(sc->rxdesc_tag);

	/* Clean up TX DMA resources. */
	for (idx = 0; idx < TX_DESC_COUNT; ++idx) {
		if ((map = sc->txbuf_map[idx].map) != NULL) {
			/* TX maps are already unloaded. */
			bus_dmamap_destroy(sc->txbuf_tag, map);
		}
	}
	if (sc->txbuf_tag != NULL)
		bus_dma_tag_destroy(sc->txbuf_tag);
	if (sc->txdesc_map != NULL) {
		bus_dmamap_unload(sc->txdesc_tag, sc->txdesc_map);
		bus_dmamap_destroy(sc->txdesc_tag, sc->txdesc_map);
	}
	if (sc->txdesc_tag != NULL)
		bus_dma_tag_destroy(sc->txdesc_tag);

	/* Release bus resources. */
	for (irq = 0; irq < MAX_IRQ_COUNT; ++irq) {
		if (sc->intr_cookie[irq] != NULL) {
			bus_teardown_intr(dev, sc->irq_res[irq],
			    sc->intr_cookie[irq]);
		}
	}
	bus_release_resources(dev, irq_res_spec, sc->irq_res);

	if (sc->mem_res != NULL)
		bus_release_resource(dev, SYS_RES_MEMORY, 0, sc->mem_res);

	FFEC_LOCK_DESTROY(sc);
	return (0);
}