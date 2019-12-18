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
struct sge_chain_data {int /*<<< orphan*/  sge_rxmbuf_tag; struct sge_rxdesc* sge_rxdesc; } ;
struct sge_softc {struct sge_chain_data sge_cdata; } ;
struct sge_rxdesc {int /*<<< orphan*/ * rx_m; int /*<<< orphan*/  rx_dmamap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 int SGE_RX_RING_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sge_list_rx_free(struct sge_softc *sc)
{
	struct sge_chain_data *cd;
	struct sge_rxdesc *rxd;
	int i;

	SGE_LOCK_ASSERT(sc);
	cd = &sc->sge_cdata;
	for (i = 0; i < SGE_RX_RING_CNT; i++) {
		rxd = &cd->sge_rxdesc[i];
		if (rxd->rx_m != NULL) {
			bus_dmamap_sync(cd->sge_rxmbuf_tag, rxd->rx_dmamap,
			    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(cd->sge_rxmbuf_tag,
			    rxd->rx_dmamap);
			m_freem(rxd->rx_m);
			rxd->rx_m = NULL;
		}
	}
	return (0);
}