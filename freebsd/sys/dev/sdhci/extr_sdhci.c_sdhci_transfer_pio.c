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
struct sdhci_slot {scalar_t__ offset; TYPE_1__* curcmd; } ;
struct TYPE_4__ {int flags; scalar_t__ len; } ;
struct TYPE_3__ {TYPE_2__* data; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 int RD4 (struct sdhci_slot*,int /*<<< orphan*/ ) ; 
 int SDHCI_DATA_AVAILABLE ; 
 int /*<<< orphan*/  SDHCI_PRESENT_STATE ; 
 int SDHCI_SPACE_AVAILABLE ; 
 int /*<<< orphan*/  sdhci_read_block_pio (struct sdhci_slot*) ; 
 int /*<<< orphan*/  sdhci_write_block_pio (struct sdhci_slot*) ; 

__attribute__((used)) static void
sdhci_transfer_pio(struct sdhci_slot *slot)
{

	/* Read as many blocks as possible. */
	if (slot->curcmd->data->flags & MMC_DATA_READ) {
		while (RD4(slot, SDHCI_PRESENT_STATE) &
		    SDHCI_DATA_AVAILABLE) {
			sdhci_read_block_pio(slot);
			if (slot->offset >= slot->curcmd->data->len)
				break;
		}
	} else {
		while (RD4(slot, SDHCI_PRESENT_STATE) &
		    SDHCI_SPACE_AVAILABLE) {
			sdhci_write_block_pio(slot);
			if (slot->offset >= slot->curcmd->data->len)
				break;
		}
	}
}