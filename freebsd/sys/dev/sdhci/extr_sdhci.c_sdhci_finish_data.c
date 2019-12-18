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
typedef  int /*<<< orphan*/  u_char ;
struct sdhci_slot {int data_done; int flags; size_t offset; scalar_t__ cmd_done; int /*<<< orphan*/  retune_req; TYPE_1__* curcmd; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; int /*<<< orphan*/  sdma_bbufsz; int /*<<< orphan*/  dmamem; int /*<<< orphan*/  intmask; } ;
struct mmc_data {int flags; size_t len; scalar_t__ data; } ;
struct TYPE_2__ {scalar_t__ error; struct mmc_data* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int MMC_DATA_READ ; 
 scalar_t__ MMC_ERR_BADCRC ; 
 int /*<<< orphan*/  SDHCI_INT_RESPONSE ; 
 int /*<<< orphan*/  SDHCI_RESET_CMD ; 
 int /*<<< orphan*/  SDHCI_RESET_DATA ; 
 int /*<<< orphan*/  SDHCI_RETUNE_REQ_RESET ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int SDHCI_USE_DMA ; 
 int /*<<< orphan*/  WR4 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_reset (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdhci_start (struct sdhci_slot*) ; 
 int /*<<< orphan*/  ulmin (size_t,int /*<<< orphan*/ ) ; 

void
sdhci_finish_data(struct sdhci_slot *slot)
{
	struct mmc_data *data = slot->curcmd->data;
	size_t left;

	/* Interrupt aggregation: Restore command interrupt.
	 * Auxiliary restore point for the case when data interrupt
	 * happened first. */
	if (!slot->cmd_done) {
		WR4(slot, SDHCI_SIGNAL_ENABLE,
		    slot->intmask |= SDHCI_INT_RESPONSE);
	}
	/* Unload rest of data from DMA buffer. */
	if (!slot->data_done && (slot->flags & SDHCI_USE_DMA) &&
	    slot->curcmd->data != NULL) {
		if (data->flags & MMC_DATA_READ) {
			left = data->len - slot->offset;
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_POSTREAD);
			memcpy((u_char*)data->data + slot->offset, slot->dmamem,
			    ulmin(left, slot->sdma_bbufsz));
		} else
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_POSTWRITE);
	}
	slot->data_done = 1;
	/* If there was error - reset the host. */
	if (slot->curcmd->error) {
		if (slot->curcmd->error == MMC_ERR_BADCRC)
			slot->retune_req |= SDHCI_RETUNE_REQ_RESET;
		sdhci_reset(slot, SDHCI_RESET_CMD);
		sdhci_reset(slot, SDHCI_RESET_DATA);
		sdhci_start(slot);
		return;
	}
	/* If we already have command response - finish. */
	if (slot->cmd_done)
		sdhci_start(slot);
}