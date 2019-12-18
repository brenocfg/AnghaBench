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
struct TYPE_2__ {int /*<<< orphan*/  dd_desc_paddr; scalar_t__ dd_desc; } ;
struct ath_softc {TYPE_1__ sc_txsdma; int /*<<< orphan*/  sc_ah; int /*<<< orphan*/  sc_tx_statuslen; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH_TXSTATUS_RING_SIZE ; 
 int HAL_NUM_TX_QUEUES ; 
 int ath_descdma_alloc_desc (struct ath_softc*,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_edma_setup_txfifo (struct ath_softc*,int) ; 
 int /*<<< orphan*/  ath_hal_setuptxstatusring (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ath_edma_dma_txsetup(struct ath_softc *sc)
{
	int error;
	int i;

	error = ath_descdma_alloc_desc(sc, &sc->sc_txsdma,
	    NULL, "txcomp", sc->sc_tx_statuslen, ATH_TXSTATUS_RING_SIZE);
	if (error != 0)
		return (error);

	ath_hal_setuptxstatusring(sc->sc_ah,
	    (void *) sc->sc_txsdma.dd_desc,
	    sc->sc_txsdma.dd_desc_paddr,
	    ATH_TXSTATUS_RING_SIZE);

	for (i = 0; i < HAL_NUM_TX_QUEUES; i++) {
		ath_edma_setup_txfifo(sc, i);
	}

	return (0);
}