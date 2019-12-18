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
struct stge_softc {int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int CSR_READ_4 (struct stge_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DELAY (int) ; 
 int DMAC_TxDMAInProg ; 
 int /*<<< orphan*/  STGE_DMACtrl ; 
 int STGE_TIMEOUT ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
stge_dma_wait(struct stge_softc *sc)
{
	int i;

	for (i = 0; i < STGE_TIMEOUT; i++) {
		DELAY(2);
		if ((CSR_READ_4(sc, STGE_DMACtrl) & DMAC_TxDMAInProg) == 0)
			break;
	}

	if (i == STGE_TIMEOUT)
		device_printf(sc->sc_dev, "DMA wait timed out\n");
}