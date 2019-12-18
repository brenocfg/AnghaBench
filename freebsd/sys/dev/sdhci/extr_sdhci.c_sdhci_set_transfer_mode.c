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
typedef  int /*<<< orphan*/  uint16_t ;
struct sdhci_slot {int quirks; int flags; TYPE_4__* req; TYPE_3__* ccb; } ;
struct mmc_data {int len; int block_count; int flags; } ;
struct TYPE_8__ {int /*<<< orphan*/ * stop; } ;
struct TYPE_5__ {scalar_t__ opcode; } ;
struct TYPE_6__ {TYPE_1__ stop; } ;
struct TYPE_7__ {TYPE_2__ mmcio; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 scalar_t__ MMC_STOP_TRANSMISSION ; 
 int SDHCI_QUIRK_BROKEN_AUTO_STOP ; 
 int /*<<< orphan*/  SDHCI_TRANSFER_MODE ; 
 int /*<<< orphan*/  SDHCI_TRNS_ACMD12 ; 
 int /*<<< orphan*/  SDHCI_TRNS_BLK_CNT_EN ; 
 int /*<<< orphan*/  SDHCI_TRNS_DMA ; 
 int /*<<< orphan*/  SDHCI_TRNS_MULTI ; 
 int /*<<< orphan*/  SDHCI_TRNS_READ ; 
 int SDHCI_USE_DMA ; 
 int /*<<< orphan*/  WR2 (struct sdhci_slot*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ __predict_true (int) ; 

__attribute__((used)) static void
sdhci_set_transfer_mode(struct sdhci_slot *slot, const struct mmc_data *data)
{
	uint16_t mode;

	if (data == NULL)
		return;

	mode = SDHCI_TRNS_BLK_CNT_EN;
	if (data->len > 512 || data->block_count > 1) {
		mode |= SDHCI_TRNS_MULTI;
		if (data->block_count == 0 && __predict_true(
#ifdef MMCCAM
		    slot->ccb->mmcio.stop.opcode == MMC_STOP_TRANSMISSION &&
#else
		    slot->req->stop != NULL &&
#endif
		    !(slot->quirks & SDHCI_QUIRK_BROKEN_AUTO_STOP)))
			mode |= SDHCI_TRNS_ACMD12;
	}
	if (data->flags & MMC_DATA_READ)
		mode |= SDHCI_TRNS_READ;
	if (slot->flags & SDHCI_USE_DMA)
		mode |= SDHCI_TRNS_DMA;

	WR2(slot, SDHCI_TRANSFER_MODE, mode);
}