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
struct sge_txdesc {scalar_t__ tx_ndesc; int /*<<< orphan*/ * tx_m; int /*<<< orphan*/  tx_dmamap; } ;
struct sge_chain_data {int /*<<< orphan*/  sge_txmbuf_tag; struct sge_txdesc* sge_txdesc; } ;
struct sge_softc {struct sge_chain_data sge_cdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  SGE_LOCK_ASSERT (struct sge_softc*) ; 
 int SGE_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sge_list_tx_free(struct sge_softc *sc)
{
	struct sge_chain_data *cd;
	struct sge_txdesc *txd;
	int i;

	SGE_LOCK_ASSERT(sc);
	cd = &sc->sge_cdata;
	for (i = 0; i < SGE_TX_RING_CNT; i++) {
		txd = &cd->sge_txdesc[i];
		if (txd->tx_m != NULL) {
			bus_dmamap_sync(cd->sge_txmbuf_tag, txd->tx_dmamap,
			    BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(cd->sge_txmbuf_tag, txd->tx_dmamap);
			m_freem(txd->tx_m);
			txd->tx_m = NULL;
			txd->tx_ndesc = 0;
		}
	}

	return (0);
}