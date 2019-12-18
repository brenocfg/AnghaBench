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
typedef  int /*<<< orphan*/  uint32_t ;
struct sdhci_slot {TYPE_2__* curcmd; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {TYPE_1__* data; } ;
struct TYPE_3__ {int flags; } ;

/* Variables and functions */
 int MMC_DATA_READ ; 
 int /*<<< orphan*/  bcm_sdhci_read_dma (int /*<<< orphan*/ ,struct sdhci_slot*) ; 
 int /*<<< orphan*/  bcm_sdhci_write_dma (int /*<<< orphan*/ ,struct sdhci_slot*) ; 

__attribute__((used)) static void
bcm_sdhci_start_transfer(device_t dev, struct sdhci_slot *slot,
    uint32_t *intmask)
{

	/* DMA transfer FIFO 1KB */
	if (slot->curcmd->data->flags & MMC_DATA_READ)
		bcm_sdhci_read_dma(dev, slot);
	else
		bcm_sdhci_write_dma(dev, slot);
}