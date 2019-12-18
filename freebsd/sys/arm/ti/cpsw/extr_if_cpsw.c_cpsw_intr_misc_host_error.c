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
typedef  int uint32_t ;
struct TYPE_4__ {int /*<<< orphan*/  active; } ;
struct TYPE_3__ {int /*<<< orphan*/  active; } ;
struct cpsw_softc {TYPE_2__ rx; TYPE_1__ tx; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPSW_CPDMA_DMASTATUS ; 
 int /*<<< orphan*/  CPSW_CPDMA_DMA_INTMASK_CLEAR ; 
 int /*<<< orphan*/  CPSW_CPDMA_DMA_INTSTAT_MASKED ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_CP (int) ; 
 int /*<<< orphan*/  CPSW_CPDMA_RX_HDP (int) ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_CP (int) ; 
 int /*<<< orphan*/  CPSW_CPDMA_TX_HDP (int) ; 
 int /*<<< orphan*/  cpsw_ale_dump_table (struct cpsw_softc*) ; 
 int /*<<< orphan*/  cpsw_dump_queue (struct cpsw_softc*,int /*<<< orphan*/ *) ; 
 int cpsw_read_4 (struct cpsw_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpsw_write_4 (struct cpsw_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
cpsw_intr_misc_host_error(struct cpsw_softc *sc)
{
	uint32_t intstat;
	uint32_t dmastat;
	int txerr, rxerr, txchan, rxchan;

	printf("\n\n");
	device_printf(sc->dev,
	    "HOST ERROR:  PROGRAMMING ERROR DETECTED BY HARDWARE\n");
	printf("\n\n");
	intstat = cpsw_read_4(sc, CPSW_CPDMA_DMA_INTSTAT_MASKED);
	device_printf(sc->dev, "CPSW_CPDMA_DMA_INTSTAT_MASKED=0x%x\n", intstat);
	dmastat = cpsw_read_4(sc, CPSW_CPDMA_DMASTATUS);
	device_printf(sc->dev, "CPSW_CPDMA_DMASTATUS=0x%x\n", dmastat);

	txerr = (dmastat >> 20) & 15;
	txchan = (dmastat >> 16) & 7;
	rxerr = (dmastat >> 12) & 15;
	rxchan = (dmastat >> 8) & 7;

	switch (txerr) {
	case 0: break;
	case 1:	printf("SOP error on TX channel %d\n", txchan);
		break;
	case 2:	printf("Ownership bit not set on SOP buffer on TX channel %d\n", txchan);
		break;
	case 3:	printf("Zero Next Buffer but not EOP on TX channel %d\n", txchan);
		break;
	case 4:	printf("Zero Buffer Pointer on TX channel %d\n", txchan);
		break;
	case 5:	printf("Zero Buffer Length on TX channel %d\n", txchan);
		break;
	case 6:	printf("Packet length error on TX channel %d\n", txchan);
		break;
	default: printf("Unknown error on TX channel %d\n", txchan);
		break;
	}

	if (txerr != 0) {
		printf("CPSW_CPDMA_TX%d_HDP=0x%x\n",
		    txchan, cpsw_read_4(sc, CPSW_CPDMA_TX_HDP(txchan)));
		printf("CPSW_CPDMA_TX%d_CP=0x%x\n",
		    txchan, cpsw_read_4(sc, CPSW_CPDMA_TX_CP(txchan)));
		cpsw_dump_queue(sc, &sc->tx.active);
	}

	switch (rxerr) {
	case 0: break;
	case 2:	printf("Ownership bit not set on RX channel %d\n", rxchan);
		break;
	case 4:	printf("Zero Buffer Pointer on RX channel %d\n", rxchan);
		break;
	case 5:	printf("Zero Buffer Length on RX channel %d\n", rxchan);
		break;
	case 6:	printf("Buffer offset too big on RX channel %d\n", rxchan);
		break;
	default: printf("Unknown RX error on RX channel %d\n", rxchan);
		break;
	}

	if (rxerr != 0) {
		printf("CPSW_CPDMA_RX%d_HDP=0x%x\n",
		    rxchan, cpsw_read_4(sc,CPSW_CPDMA_RX_HDP(rxchan)));
		printf("CPSW_CPDMA_RX%d_CP=0x%x\n",
		    rxchan, cpsw_read_4(sc, CPSW_CPDMA_RX_CP(rxchan)));
		cpsw_dump_queue(sc, &sc->rx.active);
	}

	printf("\nALE Table\n");
	cpsw_ale_dump_table(sc);

	// XXX do something useful here??
	panic("CPSW HOST ERROR INTERRUPT");

	// Suppress this interrupt in the future.
	cpsw_write_4(sc, CPSW_CPDMA_DMA_INTMASK_CLEAR, intstat);
	printf("XXX HOST ERROR INTERRUPT SUPPRESSED\n");
	// The watchdog will probably reset the controller
	// in a little while.  It will probably fail again.
}