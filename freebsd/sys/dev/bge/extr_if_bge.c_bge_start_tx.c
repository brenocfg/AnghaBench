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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  bge_tx_ring_map; int /*<<< orphan*/  bge_tx_ring_tag; } ;
struct bge_softc {scalar_t__ bge_chiprev; int /*<<< orphan*/  bge_timer; int /*<<< orphan*/  bge_tx_prodidx; TYPE_1__ bge_cdata; } ;

/* Variables and functions */
 scalar_t__ BGE_CHIPREV_5700_BX ; 
 int /*<<< orphan*/  BGE_MBX_TX_HOST_PROD0_LO ; 
 int /*<<< orphan*/  BGE_TX_TIMEOUT ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bge_writembx (struct bge_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bge_start_tx(struct bge_softc *sc, uint32_t prodidx)
{

	bus_dmamap_sync(sc->bge_cdata.bge_tx_ring_tag,
	    sc->bge_cdata.bge_tx_ring_map, BUS_DMASYNC_PREWRITE);
	/* Transmit. */
	bge_writembx(sc, BGE_MBX_TX_HOST_PROD0_LO, prodidx);
	/* 5700 b2 errata */
	if (sc->bge_chiprev == BGE_CHIPREV_5700_BX)
		bge_writembx(sc, BGE_MBX_TX_HOST_PROD0_LO, prodidx);

	sc->bge_tx_prodidx = prodidx;

	/* Set a timeout in case the chip goes out to lunch. */
	sc->bge_timer = BGE_TX_TIMEOUT;
}