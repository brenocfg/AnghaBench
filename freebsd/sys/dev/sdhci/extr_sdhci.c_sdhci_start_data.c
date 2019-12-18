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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct sdhci_slot {int data_done; int quirks; int timeout_clk; int opt; int flags; int sdma_bbufsz; int /*<<< orphan*/  sdma_boundary; scalar_t__ offset; int /*<<< orphan*/  intmask; int /*<<< orphan*/  paddr; int /*<<< orphan*/  dmamap; int /*<<< orphan*/  dmatag; int /*<<< orphan*/  dmamem; TYPE_1__* curcmd; } ;
struct mmc_data {int len; int flags; int block_count; int /*<<< orphan*/  block_size; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_PREREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_PREWRITE ; 
 int MMC_DATA_BLOCK_SIZE ; 
 int MMC_DATA_READ ; 
 int MMC_RSP_BUSY ; 
 int /*<<< orphan*/  SDHCI_BLOCK_COUNT ; 
 int /*<<< orphan*/  SDHCI_BLOCK_SIZE ; 
 int /*<<< orphan*/  SDHCI_DMA_ADDRESS ; 
 int SDHCI_HAVE_DMA ; 
 int /*<<< orphan*/  SDHCI_INT_DMA_END ; 
 int SDHCI_MAKE_BLKSZ (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SDHCI_QUIRK_32BIT_DMA_SIZE ; 
 int SDHCI_QUIRK_BROKEN_TIMEOUT_VAL ; 
 int SDHCI_QUIRK_BROKEN_TIMINGS ; 
 int SDHCI_QUIRK_INCR_TIMEOUT_CONTROL ; 
 int /*<<< orphan*/  SDHCI_SIGNAL_ENABLE ; 
 int /*<<< orphan*/  SDHCI_TIMEOUT_CONTROL ; 
 int SDHCI_USE_DMA ; 
 int /*<<< orphan*/  WR1 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WR2 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WR4 (struct sdhci_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int howmany (int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sdhci_debug ; 
 int /*<<< orphan*/  slot_printf (struct sdhci_slot*,char*,int,int) ; 
 int /*<<< orphan*/  ulmin (int,int) ; 

__attribute__((used)) static void
sdhci_start_data(struct sdhci_slot *slot, const struct mmc_data *data)
{
	uint32_t blkcnt, blksz, current_timeout, sdma_bbufsz, target_timeout;
	uint8_t div;

	if (data == NULL && (slot->curcmd->flags & MMC_RSP_BUSY) == 0) {
		slot->data_done = 1;
		return;
	}

	slot->data_done = 0;

	/* Calculate and set data timeout.*/
	/* XXX: We should have this from mmc layer, now assume 1 sec. */
	if (slot->quirks & SDHCI_QUIRK_BROKEN_TIMEOUT_VAL) {
		div = 0xE;
	} else {
		target_timeout = 1000000;
		div = 0;
		current_timeout = (1 << 13) * 1000 / slot->timeout_clk;
		while (current_timeout < target_timeout && div < 0xE) {
			++div;
			current_timeout <<= 1;
		}
		/* Compensate for an off-by-one error in the CaFe chip.*/
		if (div < 0xE &&
		    (slot->quirks & SDHCI_QUIRK_INCR_TIMEOUT_CONTROL)) {
			++div;
		}
	}
	WR1(slot, SDHCI_TIMEOUT_CONTROL, div);

	if (data == NULL)
		return;

	/* Use DMA if possible. */
	if ((slot->opt & SDHCI_HAVE_DMA))
		slot->flags |= SDHCI_USE_DMA;
	/* If data is small, broken DMA may return zeroes instead of data. */
	if ((slot->quirks & SDHCI_QUIRK_BROKEN_TIMINGS) &&
	    (data->len <= 512))
		slot->flags &= ~SDHCI_USE_DMA;
	/* Some controllers require even block sizes. */
	if ((slot->quirks & SDHCI_QUIRK_32BIT_DMA_SIZE) &&
	    ((data->len) & 0x3))
		slot->flags &= ~SDHCI_USE_DMA;
	/* Load DMA buffer. */
	if (slot->flags & SDHCI_USE_DMA) {
		sdma_bbufsz = slot->sdma_bbufsz;
		if (data->flags & MMC_DATA_READ)
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_PREREAD);
		else {
			memcpy(slot->dmamem, data->data, ulmin(data->len,
			    sdma_bbufsz));
			bus_dmamap_sync(slot->dmatag, slot->dmamap,
			    BUS_DMASYNC_PREWRITE);
		}
		WR4(slot, SDHCI_DMA_ADDRESS, slot->paddr);
		/*
		 * Interrupt aggregation: Mask border interrupt for the last
		 * bounce buffer and unmask otherwise.
		 */
		if (data->len == sdma_bbufsz)
			slot->intmask &= ~SDHCI_INT_DMA_END;
		else
			slot->intmask |= SDHCI_INT_DMA_END;
		WR4(slot, SDHCI_SIGNAL_ENABLE, slot->intmask);
	}
	/* Current data offset for both PIO and DMA. */
	slot->offset = 0;
#ifdef MMCCAM
	if (data->flags & MMC_DATA_BLOCK_SIZE) {
		/* Set block size and request border interrupts on the SDMA boundary. */
		blksz = SDHCI_MAKE_BLKSZ(slot->sdma_boundary, data->block_size);
		blkcnt = data->block_count;
		if (__predict_false(sdhci_debug > 0))
			slot_printf(slot, "SDIO Custom block params: blksz: "
			    "%#10x, blk cnt: %#10x\n", blksz, blkcnt);
	} else
#endif
	{
		/* Set block size and request border interrupts on the SDMA boundary. */
		blksz = SDHCI_MAKE_BLKSZ(slot->sdma_boundary, ulmin(data->len, 512));
		blkcnt = howmany(data->len, 512);
	}

	WR2(slot, SDHCI_BLOCK_SIZE, blksz);
	WR2(slot, SDHCI_BLOCK_COUNT, blkcnt);
	if (__predict_false(sdhci_debug > 1))
		slot_printf(slot, "Blk size: 0x%08x | Blk cnt:  0x%08x\n",
		    blksz, blkcnt);
}