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
struct bfe_softc {int /*<<< orphan*/  bfe_rx_map; int /*<<< orphan*/  bfe_rx_tag; int /*<<< orphan*/  bfe_rx_list; TYPE_1__* bfe_rx_ring; int /*<<< orphan*/  bfe_rxmbuf_tag; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bfe_mbuf; int /*<<< orphan*/  bfe_map; } ;

/* Variables and functions */
 int BFE_RX_LIST_CNT ; 
 int /*<<< orphan*/  BFE_RX_LIST_SIZE ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfe_rx_ring_free(struct bfe_softc *sc)
{
	int i;

	for (i = 0; i < BFE_RX_LIST_CNT; i++) {
		if (sc->bfe_rx_ring[i].bfe_mbuf != NULL) {
			bus_dmamap_sync(sc->bfe_rxmbuf_tag,
			    sc->bfe_rx_ring[i].bfe_map, BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->bfe_rxmbuf_tag,
			    sc->bfe_rx_ring[i].bfe_map);
			m_freem(sc->bfe_rx_ring[i].bfe_mbuf);
			sc->bfe_rx_ring[i].bfe_mbuf = NULL;
		}
	}
	bzero(sc->bfe_rx_list, BFE_RX_LIST_SIZE);
	bus_dmamap_sync(sc->bfe_rx_tag, sc->bfe_rx_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}