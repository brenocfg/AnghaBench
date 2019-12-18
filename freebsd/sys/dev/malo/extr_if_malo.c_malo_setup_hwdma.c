#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  dd_desc_paddr; } ;
struct malo_txq {TYPE_1__ dma; } ;
struct TYPE_5__ {int maxnum_wcb; int /*<<< orphan*/  maxnum_txwcb; int /*<<< orphan*/ * wcbbase; int /*<<< orphan*/  rxdesc_read; } ;
struct TYPE_6__ {int /*<<< orphan*/  dd_desc_paddr; } ;
struct malo_softc {TYPE_2__ malo_hwdma; struct malo_txq* malo_txq; TYPE_3__ malo_rxdma; } ;

/* Variables and functions */
 int MALO_NUM_TX_QUEUES ; 
 int /*<<< orphan*/  malo_hal_set_rxtxdma (struct malo_softc*) ; 
 int /*<<< orphan*/  malo_txbuf ; 

__attribute__((used)) static int
malo_setup_hwdma(struct malo_softc *sc)
{
	int i;
	struct malo_txq *txq;

	sc->malo_hwdma.rxdesc_read = sc->malo_rxdma.dd_desc_paddr;

	for (i = 0; i < MALO_NUM_TX_QUEUES; i++) {
		txq = &sc->malo_txq[i];
		sc->malo_hwdma.wcbbase[i] = txq->dma.dd_desc_paddr;
	}
	sc->malo_hwdma.maxnum_txwcb = malo_txbuf;
	sc->malo_hwdma.maxnum_wcb = MALO_NUM_TX_QUEUES;

	malo_hal_set_rxtxdma(sc);

	return 0;
}