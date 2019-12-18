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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct sdhci_slot {int offset; int intmask; int /*<<< orphan*/  mtx; int /*<<< orphan*/  bus; TYPE_2__* curcmd; } ;
struct bcm_sdhci_softc {scalar_t__ dmamap_seg_index; scalar_t__ dmamap_seg_count; scalar_t__ dmamap_status; int /*<<< orphan*/  sc_dma_map; int /*<<< orphan*/  sc_dma_tag; int /*<<< orphan*/  sc_dev; struct sdhci_slot sc_slot; } ;
struct TYPE_4__ {int /*<<< orphan*/  error; TYPE_1__* data; } ;
struct TYPE_3__ {int flags; int len; scalar_t__ data; } ;

/* Variables and functions */
 int BCM_SDHCI_BUFFER_SIZE ; 
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMA_NOWAIT ; 
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  MMC_ERR_NO_MEMORY ; 
 int SDHCI_INT_DATA_AVAIL ; 
 int SDHCI_INT_DATA_END ; 
 int SDHCI_INT_SPACE_AVAIL ; 
 int /*<<< orphan*/  SDHCI_INT_STATUS ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  bcm_sdhci_dmacb ; 
 int bcm_sdhci_read_4 (int /*<<< orphan*/ ,struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcm_sdhci_start_dma_seg (struct bcm_sdhci_softc*) ; 
 int /*<<< orphan*/  bcm_sdhci_write_4 (int /*<<< orphan*/ ,struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct bcm_sdhci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sdhci_finish_data (struct sdhci_slot*) ; 

__attribute__((used)) static void
bcm_sdhci_dma_intr(int ch, void *arg)
{
	struct bcm_sdhci_softc *sc = (struct bcm_sdhci_softc *)arg;
	struct sdhci_slot *slot = &sc->sc_slot;
	uint32_t reg, mask;
	int left, sync_op;

	mtx_lock(&slot->mtx);

	if (slot->curcmd == NULL) {
		mtx_unlock(&slot->mtx);
		device_printf(sc->sc_dev,
		    "command aborted in the middle of DMA\n");
		return;
	}

	/*
	 * If there are more segments for the current dma, start the next one.
	 * Otherwise unload the dma map and decide what to do next based on the
	 * status of the sdhci controller and whether there's more data left.
	 */
	if (sc->dmamap_seg_index < sc->dmamap_seg_count) {
		bcm_sdhci_start_dma_seg(sc);
		mtx_unlock(&slot->mtx);
		return;
	}

	if (slot->curcmd->data->flags & MMC_DATA_READ) {
		sync_op = BUS_DMASYNC_POSTREAD;
		mask = SDHCI_INT_DATA_AVAIL;
	} else {
		sync_op = BUS_DMASYNC_POSTWRITE;
		mask = SDHCI_INT_SPACE_AVAIL;
	}
	bus_dmamap_sync(sc->sc_dma_tag, sc->sc_dma_map, sync_op);
	bus_dmamap_unload(sc->sc_dma_tag, sc->sc_dma_map);

	sc->dmamap_seg_count = 0;
	sc->dmamap_seg_index = 0;

	left = min(BCM_SDHCI_BUFFER_SIZE,
	    slot->curcmd->data->len - slot->offset);

	/*
	 * If there is less than buffer size outstanding, we would not handle
	 * it anymore using DMA if bcm_sdhci_will_handle_transfer() were asked.
	 * Re-enable interrupts and return and let the SDHCI state machine
	 * finish the job.
	 */
	if (left < BCM_SDHCI_BUFFER_SIZE) {
		/* Re-enable data interrupts. */
		slot->intmask |= SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL |
		    SDHCI_INT_DATA_END;
		bcm_sdhci_write_4(slot->bus, slot, SDHCI_SIGNAL_ENABLE,
		    slot->intmask);
		mtx_unlock(&slot->mtx);
		return;
	}

	/* DATA END? */
	reg = bcm_sdhci_read_4(slot->bus, slot, SDHCI_INT_STATUS);

	if (reg & SDHCI_INT_DATA_END) {
		/* ACK for all outstanding interrupts */
		bcm_sdhci_write_4(slot->bus, slot, SDHCI_INT_STATUS, reg);

		/* enable INT */
		slot->intmask |= SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL
		    | SDHCI_INT_DATA_END;
		bcm_sdhci_write_4(slot->bus, slot, SDHCI_SIGNAL_ENABLE,
		    slot->intmask);

		/* finish this data */
		sdhci_finish_data(slot);
	} 
	else {
		/* already available? */
		if (reg & mask) {

			/* ACK for DATA_AVAIL or SPACE_AVAIL */
			bcm_sdhci_write_4(slot->bus, slot,
			    SDHCI_INT_STATUS, mask);

			/* continue next DMA transfer */
			if (bus_dmamap_load(sc->sc_dma_tag, sc->sc_dma_map, 
			    (uint8_t *)slot->curcmd->data->data + 
			    slot->offset, left, bcm_sdhci_dmacb, sc, 
			    BUS_DMA_NOWAIT) != 0 || sc->dmamap_status != 0) {
				slot->curcmd->error = MMC_ERR_NO_MEMORY;
				sdhci_finish_data(slot);
			} else {
				bcm_sdhci_start_dma_seg(sc);
			}
		} else {
			/* wait for next data by INT */

			/* enable INT */
			slot->intmask |= SDHCI_INT_DATA_AVAIL |
			    SDHCI_INT_SPACE_AVAIL | SDHCI_INT_DATA_END;
			bcm_sdhci_write_4(slot->bus, slot, SDHCI_SIGNAL_ENABLE,
			    slot->intmask);
		}
	}

	mtx_unlock(&slot->mtx);
}