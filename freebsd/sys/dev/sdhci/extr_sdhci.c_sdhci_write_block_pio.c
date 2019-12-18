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
struct sdhci_slot {scalar_t__ offset; TYPE_2__* curcmd; } ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {char* data; int flags; int block_size; scalar_t__ len; } ;

/* Variables and functions */
 int MMC_DATA_BLOCK_SIZE ; 
 int /*<<< orphan*/  SDHCI_BUFFER ; 
 int /*<<< orphan*/  WR4 (struct sdhci_slot*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WR_MULTI_4 (struct sdhci_slot*,int /*<<< orphan*/ ,int*,size_t) ; 
 size_t min (int,scalar_t__) ; 

__attribute__((used)) static void
sdhci_write_block_pio(struct sdhci_slot *slot)
{
	uint32_t data = 0;
	char *buffer;
	size_t left;

	buffer = slot->curcmd->data->data;
	buffer += slot->offset;
	/* Transfer one block at a time. */
#ifdef MMCCAM
	if (slot->curcmd->data->flags & MMC_DATA_BLOCK_SIZE) {
		left = min(slot->curcmd->data->block_size,
		    slot->curcmd->data->len - slot->offset);
	} else
#endif
		left = min(512, slot->curcmd->data->len - slot->offset);
	slot->offset += left;

	/* Handle unaligned and aligned buffer cases. */
	if ((intptr_t)buffer & 3) {
		while (left > 3) {
			data = buffer[0] +
			    (buffer[1] << 8) +
			    (buffer[2] << 16) +
			    (buffer[3] << 24);
			left -= 4;
			buffer += 4;
			WR4(slot, SDHCI_BUFFER, data);
		}
	} else {
		WR_MULTI_4(slot, SDHCI_BUFFER,
		    (uint32_t *)buffer, left >> 2);
		left &= 3;
	}
	/* Handle uneven size case. */
	if (left > 0) {
		while (left > 0) {
			data <<= 8;
			data += *(buffer++);
			left--;
		}
		WR4(slot, SDHCI_BUFFER, data);
	}
}