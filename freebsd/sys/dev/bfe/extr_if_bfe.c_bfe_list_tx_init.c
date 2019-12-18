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
struct bfe_softc {int /*<<< orphan*/  bfe_tx_map; int /*<<< orphan*/  bfe_tx_tag; TYPE_1__* bfe_tx_ring; int /*<<< orphan*/  bfe_tx_list; scalar_t__ bfe_tx_cons; scalar_t__ bfe_tx_prod; scalar_t__ bfe_tx_cnt; } ;
struct TYPE_2__ {int /*<<< orphan*/ * bfe_mbuf; } ;

/* Variables and functions */
 int BFE_TX_LIST_CNT ; 
 int /*<<< orphan*/  BFE_TX_LIST_SIZE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfe_list_tx_init(struct bfe_softc *sc)
{
	int i;

	sc->bfe_tx_cnt = sc->bfe_tx_prod = sc->bfe_tx_cons = 0;
	bzero(sc->bfe_tx_list, BFE_TX_LIST_SIZE);
	for (i = 0; i < BFE_TX_LIST_CNT; i++)
		sc->bfe_tx_ring[i].bfe_mbuf = NULL;

	bus_dmamap_sync(sc->bfe_tx_tag, sc->bfe_tx_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
}