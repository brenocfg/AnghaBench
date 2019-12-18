#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dd_desc_paddr; } ;
struct mwl_txq {TYPE_2__ dma; } ;
struct TYPE_8__ {int maxNumWCB; int /*<<< orphan*/  maxNumTxWcb; int /*<<< orphan*/ * wcbBase; int /*<<< orphan*/  rxDescRead; } ;
struct TYPE_7__ {int /*<<< orphan*/ * wcbBase; int /*<<< orphan*/  rxDescWrite; int /*<<< orphan*/  rxDescRead; } ;
struct TYPE_5__ {int /*<<< orphan*/  dd_desc_paddr; } ;
struct mwl_softc {int /*<<< orphan*/  sc_dev; TYPE_4__ sc_hwdma; int /*<<< orphan*/  sc_mh; TYPE_3__ sc_hwspecs; struct mwl_txq* sc_txq; TYPE_1__ sc_rxdma; } ;

/* Variables and functions */
 int MWL_NUM_ACK_QUEUES ; 
 int MWL_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  WR4 (struct mwl_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int mwl_hal_sethwdma (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  mwl_txbuf ; 

__attribute__((used)) static int
mwl_setupdma(struct mwl_softc *sc)
{
	int error, i;

	sc->sc_hwdma.rxDescRead = sc->sc_rxdma.dd_desc_paddr;
	WR4(sc, sc->sc_hwspecs.rxDescRead, sc->sc_hwdma.rxDescRead);
	WR4(sc, sc->sc_hwspecs.rxDescWrite, sc->sc_hwdma.rxDescRead);

	for (i = 0; i < MWL_NUM_TX_QUEUES-MWL_NUM_ACK_QUEUES; i++) {
		struct mwl_txq *txq = &sc->sc_txq[i];
		sc->sc_hwdma.wcbBase[i] = txq->dma.dd_desc_paddr;
		WR4(sc, sc->sc_hwspecs.wcbBase[i], sc->sc_hwdma.wcbBase[i]);
	}
	sc->sc_hwdma.maxNumTxWcb = mwl_txbuf;
	sc->sc_hwdma.maxNumWCB = MWL_NUM_TX_QUEUES-MWL_NUM_ACK_QUEUES;

	error = mwl_hal_sethwdma(sc->sc_mh, &sc->sc_hwdma);
	if (error != 0) {
		device_printf(sc->sc_dev,
		    "unable to setup tx/rx dma; hal status %u\n", error);
		/* XXX */
	}
	return error;
}