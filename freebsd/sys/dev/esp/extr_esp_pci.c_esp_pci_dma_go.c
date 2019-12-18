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
struct ncr53c9x_softc {int dummy; } ;
struct esp_pci_softc {int sc_datain; scalar_t__ sc_dmasize; int sc_active; int /*<<< orphan*/  sc_xferdmam; int /*<<< orphan*/  sc_xferdmat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int DMACMD_DIR ; 
 int DMACMD_IDLE ; 
 int DMACMD_START ; 
 int /*<<< orphan*/  DMA_CMD ; 
 int /*<<< orphan*/  WRITE_DMAREG (struct esp_pci_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
esp_pci_dma_go(struct ncr53c9x_softc *sc)
{
	struct esp_pci_softc *esc = (struct esp_pci_softc *)sc;
	int datain;

	datain = esc->sc_datain;

	/* No DMA transfer for a "Transfer Pad" operation */
	if (esc->sc_dmasize == 0)
		return;

	/* Sync the transfer buffer. */
	bus_dmamap_sync(esc->sc_xferdmat, esc->sc_xferdmam, datain != 0 ?
	    BUS_DMASYNC_PREREAD : BUS_DMASYNC_PREWRITE);

	/* Set the DMA engine to the IDLE state. */
	/* XXX DMA Transfer Interrupt Enable bit is broken? */
	WRITE_DMAREG(esc, DMA_CMD, DMACMD_IDLE | /* DMACMD_INTE | */
	    (datain != 0 ? DMACMD_DIR : 0));

	/* Issue a DMA start command. */
	WRITE_DMAREG(esc, DMA_CMD, DMACMD_START | /* DMACMD_INTE | */
	    (datain != 0 ? DMACMD_DIR : 0));

	esc->sc_active = 1;
}