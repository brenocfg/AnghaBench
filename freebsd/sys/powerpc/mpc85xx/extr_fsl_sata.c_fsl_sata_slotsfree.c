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
struct TYPE_4__ {int /*<<< orphan*/ * data_map; } ;
struct fsl_sata_slot {TYPE_2__ dma; int /*<<< orphan*/  timeout; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_tag; } ;
struct fsl_sata_channel {TYPE_1__ dma; struct fsl_sata_slot* slot; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int FSL_SATA_MAX_SLOTS ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 struct fsl_sata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fsl_sata_slotsfree(device_t dev)
{
	struct fsl_sata_channel *ch = device_get_softc(dev);
	int i;

	/* Free all dma slots */
	for (i = 0; i < FSL_SATA_MAX_SLOTS; i++) {
		struct fsl_sata_slot *slot = &ch->slot[i];

		callout_drain(&slot->timeout);
		if (slot->dma.data_map) {
			bus_dmamap_destroy(ch->dma.data_tag, slot->dma.data_map);
			slot->dma.data_map = NULL;
		}
	}
}