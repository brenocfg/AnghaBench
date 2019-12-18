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
typedef  int /*<<< orphan*/  u_char ;
struct sdhci_slot {int opt; int flags; int sdma_bbufsz; size_t offset; int intmask; int paddr; int /*<<< orphan*/  bus; TYPE_2__* curcmd; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; int /*<<< orphan*/ * dmamem; TYPE_1__* req; } ;
struct mmc_data {size_t len; int flags; scalar_t__ data; } ;
struct TYPE_4__ {int flags; scalar_t__ error; scalar_t__ opcode; struct mmc_data* data; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int MMC_DATA_READ ; 
 scalar_t__ MMC_ERR_BADCRC ; 
 scalar_t__ MMC_ERR_INVALID ; 
 scalar_t__ MMC_ERR_TIMEOUT ; 
 int MMC_RSP_BUSY ; 
 scalar_t__ MMC_SEND_TUNING_BLOCK ; 
 scalar_t__ MMC_SEND_TUNING_BLOCK_HS200 ; 
 int /*<<< orphan*/  MMC_TUNE_DONE ; 
 int PLATFORM_DATA_STARTED ; 
 int /*<<< orphan*/  SDHCI_DMA_ADDRESS ; 
 int SDHCI_INT_DATA_AVAIL ; 
 int SDHCI_INT_DATA_CRC ; 
 int SDHCI_INT_DATA_END ; 
 int SDHCI_INT_DATA_END_BIT ; 
 int SDHCI_INT_DATA_TIMEOUT ; 
 int SDHCI_INT_DMA_END ; 
 int SDHCI_INT_SPACE_AVAIL ; 
 int /*<<< orphan*/  SDHCI_PLATFORM_FINISH_TRANSFER (int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_PLATFORM_START_TRANSFER (int /*<<< orphan*/ ,struct sdhci_slot*,int*) ; 
 int SDHCI_PLATFORM_TRANSFER ; 
 scalar_t__ SDHCI_PLATFORM_WILL_HANDLE (int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  WR4 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_dumpregs (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_finish_command (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_finish_data (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_transfer_pio (struct sdhci_slot*) ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*,int) ; 
 int /*<<< orphan*/  ulmin (size_t,int) ; 

__attribute__((used)) static void
sdhci_data_irq(struct sdhci_slot *slot, uint32_t intmask)
{
	struct mmc_data *data;
	size_t left;
	uint32_t sdma_bbufsz;

	if (!slot->curcmd) {
		slot_printf(slot, "Got data interrupt 0x%08x, but "
		    "there is no active command.\n", intmask);
		sdhci_dumpregs(slot);
		return;
	}
	if (slot->curcmd->data == NULL &&
	    (slot->curcmd->flags & MMC_RSP_BUSY) == 0) {
		slot_printf(slot, "Got data interrupt 0x%08x, but "
		    "there is no active data operation.\n",
		    intmask);
		sdhci_dumpregs(slot);
		return;
	}
	if (intmask & SDHCI_INT_DATA_TIMEOUT)
		slot->curcmd->error = MMC_ERR_TIMEOUT;
	else if (intmask & (SDHCI_INT_DATA_CRC | SDHCI_INT_DATA_END_BIT))
		slot->curcmd->error = MMC_ERR_BADCRC;
	if (slot->curcmd->data == NULL &&
	    (intmask & (SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL |
	    SDHCI_INT_DMA_END))) {
		slot_printf(slot, "Got data interrupt 0x%08x, but "
		    "there is busy-only command.\n", intmask);
		sdhci_dumpregs(slot);
		slot->curcmd->error = MMC_ERR_INVALID;
	}
	if (slot->curcmd->error) {
		/* No need to continue after any error. */
		goto done;
	}

	/* Handle tuning completion interrupt. */
	if (__predict_false((intmask & SDHCI_INT_DATA_AVAIL) &&
	    (slot->curcmd->opcode == MMC_SEND_TUNING_BLOCK ||
	    slot->curcmd->opcode == MMC_SEND_TUNING_BLOCK_HS200))) {
		slot->req->flags |= MMC_TUNE_DONE;
		sdhci_finish_command(slot);
		sdhci_finish_data(slot);
		return;
	}
	/* Handle PIO interrupt. */
	if (intmask & (SDHCI_INT_DATA_AVAIL | SDHCI_INT_SPACE_AVAIL)) {
		if ((slot->opt & SDHCI_PLATFORM_TRANSFER) &&
		    SDHCI_PLATFORM_WILL_HANDLE(slot->bus, slot)) {
			SDHCI_PLATFORM_START_TRANSFER(slot->bus, slot,
			    &intmask);
			slot->flags |= PLATFORM_DATA_STARTED;
		} else
			sdhci_transfer_pio(slot);
	}
	/* Handle DMA border. */
	if (intmask & SDHCI_INT_DMA_END) {
		data = slot->curcmd->data;
		sdma_bbufsz = slot->sdma_bbufsz;

		/* Unload DMA buffer ... */
		left = data->len - slot->offset;
		if (data->flags & MMC_DATA_READ) {
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_POSTREAD);
			memcpy((u_char*)data->data + slot->offset, slot->dmamem,
			    ulmin(left, sdma_bbufsz));
		} else {
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_POSTWRITE);
		}
		/* ... and reload it again. */
		slot->offset += sdma_bbufsz;
		left = data->len - slot->offset;
		if (data->flags & MMC_DATA_READ) {
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_PREREAD);
		} else {
			memcpy(slot->dmamem, (u_char*)data->data + slot->offset,
			    ulmin(left, sdma_bbufsz));
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_PREWRITE);
		}
		/*
		 * Interrupt aggregation: Mask border interrupt for the last
		 * bounce buffer.
		 */
		if (left == sdma_bbufsz) {
			slot->intmask &= ~SDHCI_INT_DMA_END;
			WR4(slot, SDHCI_SIGNAL_ENABLE, slot->intmask);
		}
		/* Restart DMA. */
		WR4(slot, SDHCI_DMA_ADDRESS, slot->paddr);
	}
	/* We have got all data. */
	if (intmask & SDHCI_INT_DATA_END) {
		if (slot->flags & PLATFORM_DATA_STARTED) {
			slot->flags &= ~PLATFORM_DATA_STARTED;
			SDHCI_PLATFORM_FINISH_TRANSFER(slot->bus, slot);
		} else
			sdhci_finish_data(slot);
	}
done:
	if (slot->curcmd != NULL && slot->curcmd->error != 0) {
		if (slot->flags & PLATFORM_DATA_STARTED) {
			slot->flags &= ~PLATFORM_DATA_STARTED;
			SDHCI_PLATFORM_FINISH_TRANSFER(slot->bus, slot);
		} else
			sdhci_finish_data(slot);
	}
}