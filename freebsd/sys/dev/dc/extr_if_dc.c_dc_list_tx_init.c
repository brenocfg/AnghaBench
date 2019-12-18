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
struct dc_list_data {TYPE_1__* dc_tx_list; } ;
struct dc_chain_data {scalar_t__ dc_tx_pkts; scalar_t__ dc_tx_cnt; scalar_t__ dc_tx_cons; scalar_t__ dc_tx_prod; int /*<<< orphan*/ ** dc_tx_chain; } ;
struct dc_softc {int /*<<< orphan*/  dc_tx_lmap; int /*<<< orphan*/  dc_tx_ltag; struct dc_list_data dc_ldata; struct dc_chain_data dc_cdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  dc_next; scalar_t__ dc_data; scalar_t__ dc_ctl; scalar_t__ dc_status; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  DC_TXDESC (struct dc_softc*,int) ; 
 int DC_TX_LIST_CNT ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  htole32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dc_list_tx_init(struct dc_softc *sc)
{
	struct dc_chain_data *cd;
	struct dc_list_data *ld;
	int i, nexti;

	cd = &sc->dc_cdata;
	ld = &sc->dc_ldata;
	for (i = 0; i < DC_TX_LIST_CNT; i++) {
		if (i == DC_TX_LIST_CNT - 1)
			nexti = 0;
		else
			nexti = i + 1;
		ld->dc_tx_list[i].dc_status = 0;
		ld->dc_tx_list[i].dc_ctl = 0;
		ld->dc_tx_list[i].dc_data = 0;
		ld->dc_tx_list[i].dc_next = htole32(DC_TXDESC(sc, nexti));
		cd->dc_tx_chain[i] = NULL;
	}

	cd->dc_tx_prod = cd->dc_tx_cons = cd->dc_tx_cnt = 0;
	cd->dc_tx_pkts = 0;
	bus_dmamap_sync(sc->dc_tx_ltag, sc->dc_tx_lmap,
	    BUS_DMASYNC_PREWRITE | BUS_DMASYNC_PREREAD);
	return (0);
}