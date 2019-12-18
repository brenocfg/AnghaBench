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
struct TYPE_4__ {int /*<<< orphan*/  ti_rx_std_ring_map; int /*<<< orphan*/  ti_rx_std_ring_tag; int /*<<< orphan*/ ** ti_rx_std_chain; int /*<<< orphan*/  ti_rx_std_tag; int /*<<< orphan*/ * ti_rx_std_maps; } ;
struct TYPE_3__ {int /*<<< orphan*/  ti_rx_std_ring; } ;
struct ti_softc {TYPE_2__ ti_cdata; TYPE_1__ ti_rdata; } ;
typedef  int /*<<< orphan*/  bus_dmamap_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int TI_STD_RX_RING_CNT ; 
 int /*<<< orphan*/  TI_STD_RX_RING_SZ ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ti_free_rx_ring_std(struct ti_softc *sc)
{
	bus_dmamap_t map;
	int i;

	for (i = 0; i < TI_STD_RX_RING_CNT; i++) {
		if (sc->ti_cdata.ti_rx_std_chain[i] != NULL) {
			map = sc->ti_cdata.ti_rx_std_maps[i];
			bus_dmamap_sync(sc->ti_cdata.ti_rx_std_tag, map,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->ti_cdata.ti_rx_std_tag, map);
			m_freem(sc->ti_cdata.ti_rx_std_chain[i]);
			sc->ti_cdata.ti_rx_std_chain[i] = NULL;
		}
	}
	bzero(sc->ti_rdata.ti_rx_std_ring, TI_STD_RX_RING_SZ);
	bus_dmamap_sync(sc->ti_cdata.ti_rx_std_ring_tag,
	    sc->ti_cdata.ti_rx_std_ring_map, BUS_DMASYNC_PREWRITE);
}