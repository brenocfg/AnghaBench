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
struct TYPE_4__ {int /*<<< orphan*/ * bge_rx_jumbo_ring; } ;
struct TYPE_3__ {int /*<<< orphan*/ ** bge_rx_jumbo_chain; int /*<<< orphan*/ * bge_rx_jumbo_dmamap; int /*<<< orphan*/  bge_mtag_jumbo; } ;
struct bge_softc {TYPE_2__ bge_ldata; TYPE_1__ bge_cdata; } ;
struct bge_extrx_bd {int dummy; } ;

/* Variables and functions */
 int BGE_JUMBO_RX_RING_CNT ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bge_free_rx_ring_jumbo(struct bge_softc *sc)
{
	int i;

	for (i = 0; i < BGE_JUMBO_RX_RING_CNT; i++) {
		if (sc->bge_cdata.bge_rx_jumbo_chain[i] != NULL) {
			bus_dmamap_sync(sc->bge_cdata.bge_mtag_jumbo,
			    sc->bge_cdata.bge_rx_jumbo_dmamap[i],
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(sc->bge_cdata.bge_mtag_jumbo,
			    sc->bge_cdata.bge_rx_jumbo_dmamap[i]);
			m_freem(sc->bge_cdata.bge_rx_jumbo_chain[i]);
			sc->bge_cdata.bge_rx_jumbo_chain[i] = NULL;
		}
		bzero((char *)&sc->bge_ldata.bge_rx_jumbo_ring[i],
		    sizeof(struct bge_extrx_bd));
	}
}