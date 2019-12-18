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
struct sis_txdesc {int /*<<< orphan*/ * tx_m; } ;
struct sis_softc {int /*<<< orphan*/  sis_rx_list_map; int /*<<< orphan*/  sis_rx_list_tag; TYPE_1__* sis_rx_list; struct sis_rxdesc* sis_rxdesc; scalar_t__ sis_rx_cons; int /*<<< orphan*/  sis_tx_list_map; int /*<<< orphan*/  sis_tx_list_tag; scalar_t__ sis_tx_cnt; scalar_t__ sis_tx_cons; scalar_t__ sis_tx_prod; TYPE_1__* sis_tx_list; struct sis_txdesc* sis_txdesc; } ;
struct sis_rxdesc {TYPE_1__* rx_desc; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;
struct TYPE_2__ {void* sis_next; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  SIS_ADDR_LO (int /*<<< orphan*/ ) ; 
 int SIS_RX_LIST_CNT ; 
 int /*<<< orphan*/  SIS_RX_LIST_SZ ; 
 int /*<<< orphan*/  SIS_RX_RING_ADDR (struct sis_softc*,int) ; 
 int SIS_TX_LIST_CNT ; 
 int /*<<< orphan*/  SIS_TX_LIST_SZ ; 
 int /*<<< orphan*/  SIS_TX_RING_ADDR (struct sis_softc*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* htole32 (int /*<<< orphan*/ ) ; 
 int sis_newbuf (struct sis_softc*,struct sis_rxdesc*) ; 

__attribute__((used)) static int
sis_ring_init(struct sis_softc *sc)
{
	struct sis_rxdesc	*rxd;
	struct sis_txdesc	*txd;
	bus_addr_t		next;
	int			error, i;

	bzero(&sc->sis_tx_list[0], SIS_TX_LIST_SZ);
	for (i = 0; i < SIS_TX_LIST_CNT; i++) {
		txd = &sc->sis_txdesc[i];
		txd->tx_m = NULL;
		if (i == SIS_TX_LIST_CNT - 1)
			next = SIS_TX_RING_ADDR(sc, 0);
		else
			next = SIS_TX_RING_ADDR(sc, i + 1);
		sc->sis_tx_list[i].sis_next = htole32(SIS_ADDR_LO(next));
	}
	sc->sis_tx_prod = sc->sis_tx_cons = sc->sis_tx_cnt = 0;
	bus_dmamap_sync(sc->sis_tx_list_tag, sc->sis_tx_list_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	sc->sis_rx_cons = 0;
	bzero(&sc->sis_rx_list[0], SIS_RX_LIST_SZ);
	for (i = 0; i < SIS_RX_LIST_CNT; i++) {
		rxd = &sc->sis_rxdesc[i];
		rxd->rx_desc = &sc->sis_rx_list[i];
		if (i == SIS_RX_LIST_CNT - 1)
			next = SIS_RX_RING_ADDR(sc, 0);
		else
			next = SIS_RX_RING_ADDR(sc, i + 1);
		rxd->rx_desc->sis_next = htole32(SIS_ADDR_LO(next));
		error = sis_newbuf(sc, rxd);
		if (error)
			return (error);
	}
	bus_dmamap_sync(sc->sis_rx_list_tag, sc->sis_rx_list_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);

	return (0);
}