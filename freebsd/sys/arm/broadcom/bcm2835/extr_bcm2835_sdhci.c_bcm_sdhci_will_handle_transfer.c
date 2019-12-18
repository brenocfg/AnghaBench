#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sdhci_slot {scalar_t__ offset; TYPE_3__* curcmd; int /*<<< orphan*/  bus; } ;
struct bcm_sdhci_softc {TYPE_1__* conf; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {TYPE_2__* data; } ;
struct TYPE_5__ {scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  use_dma; } ;

/* Variables and functions */
 size_t BCM_DMA_BLOCK_SIZE ; 
 struct bcm_sdhci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 size_t min (size_t,scalar_t__) ; 

__attribute__((used)) static int
bcm_sdhci_will_handle_transfer(device_t dev, struct sdhci_slot *slot)
{
	struct bcm_sdhci_softc *sc = device_get_softc(slot->bus);
	size_t left;

	if (!sc->conf->use_dma)
		return (0);

	/*
	 * Do not use DMA for transfers less than block size or with a length
	 * that is not a multiple of four.
	 */
	left = min(BCM_DMA_BLOCK_SIZE,
	    slot->curcmd->data->len - slot->offset);
	if (left < BCM_DMA_BLOCK_SIZE)
		return (0);
	if (left & 0x03)
		return (0);

	return (1);
}