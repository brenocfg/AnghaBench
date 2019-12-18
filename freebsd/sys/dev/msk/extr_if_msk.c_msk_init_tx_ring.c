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
struct msk_txdesc {int /*<<< orphan*/ * tx_le; int /*<<< orphan*/ * tx_m; } ;
struct msk_tx_desc {int dummy; } ;
struct msk_ring_data {int /*<<< orphan*/ * msk_tx_ring; } ;
struct TYPE_2__ {int /*<<< orphan*/  msk_tx_ring_map; int /*<<< orphan*/  msk_tx_ring_tag; struct msk_txdesc* msk_txdesc; scalar_t__ msk_tx_high_addr; scalar_t__ msk_tx_cnt; scalar_t__ msk_tx_cons; scalar_t__ msk_tx_prod; scalar_t__ msk_last_csum; scalar_t__ msk_tso_mtu; } ;
struct msk_if_softc {TYPE_1__ msk_cdata; struct msk_ring_data msk_rdata; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int MSK_TX_RING_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
msk_init_tx_ring(struct msk_if_softc *sc_if)
{
	struct msk_ring_data *rd;
	struct msk_txdesc *txd;
	int i;

	sc_if->msk_cdata.msk_tso_mtu = 0;
	sc_if->msk_cdata.msk_last_csum = 0;
	sc_if->msk_cdata.msk_tx_prod = 0;
	sc_if->msk_cdata.msk_tx_cons = 0;
	sc_if->msk_cdata.msk_tx_cnt = 0;
	sc_if->msk_cdata.msk_tx_high_addr = 0;

	rd = &sc_if->msk_rdata;
	bzero(rd->msk_tx_ring, sizeof(struct msk_tx_desc) * MSK_TX_RING_CNT);
	for (i = 0; i < MSK_TX_RING_CNT; i++) {
		txd = &sc_if->msk_cdata.msk_txdesc[i];
		txd->tx_m = NULL;
		txd->tx_le = &rd->msk_tx_ring[i];
	}

	bus_dmamap_sync(sc_if->msk_cdata.msk_tx_ring_tag,
	    sc_if->msk_cdata.msk_tx_ring_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}