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
struct TYPE_4__ {int /*<<< orphan*/  bge_tx_ring_map; int /*<<< orphan*/  bge_tx_ring_tag; } ;
struct TYPE_3__ {int /*<<< orphan*/  bge_tx_ring; } ;
struct bge_softc {scalar_t__ bge_chiprev; scalar_t__ bge_tx_prodidx; TYPE_2__ bge_cdata; TYPE_1__ bge_ldata; scalar_t__ bge_tx_saved_considx; scalar_t__ bge_txcnt; } ;

/* Variables and functions */
 scalar_t__ BGE_CHIPREV_5700_BX ; 
 int /*<<< orphan*/  BGE_MBX_TX_HOST_PROD0_LO ; 
 int /*<<< orphan*/  BGE_MBX_TX_NIC_PROD0_LO ; 
 int /*<<< orphan*/  BGE_TX_RING_SZ ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bge_writembx (struct bge_softc*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bge_init_tx_ring(struct bge_softc *sc)
{
	sc->bge_txcnt = 0;
	sc->bge_tx_saved_considx = 0;

	bzero(sc->bge_ldata.bge_tx_ring, BGE_TX_RING_SZ);
	bus_dmamap_sync(sc->bge_cdata.bge_tx_ring_tag,
	    sc->bge_cdata.bge_tx_ring_map, BUS_DMASYNC_PREWRITE);

	/* Initialize transmit producer index for host-memory send ring. */
	sc->bge_tx_prodidx = 0;
	bge_writembx(sc, BGE_MBX_TX_HOST_PROD0_LO, sc->bge_tx_prodidx);

	/* 5700 b2 errata */
	if (sc->bge_chiprev == BGE_CHIPREV_5700_BX)
		bge_writembx(sc, BGE_MBX_TX_HOST_PROD0_LO, sc->bge_tx_prodidx);

	/* NIC-memory send ring not used; initialize to zero. */
	bge_writembx(sc, BGE_MBX_TX_NIC_PROD0_LO, 0);
	/* 5700 b2 errata */
	if (sc->bge_chiprev == BGE_CHIPREV_5700_BX)
		bge_writembx(sc, BGE_MBX_TX_NIC_PROD0_LO, 0);

	return (0);
}