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
struct ata_dmaslot {int /*<<< orphan*/ * data_tag; int /*<<< orphan*/ * sg_tag; int /*<<< orphan*/ * data_map; int /*<<< orphan*/ * sg; int /*<<< orphan*/  sg_map; scalar_t__ sg_bus; } ;
struct TYPE_2__ {struct ata_dmaslot* slot; } ;
struct ata_channel {TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ATA_DMA_SLOTS ; 
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_destroy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct ata_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ata_dmafree(device_t dev)
{
    struct ata_channel *ch = device_get_softc(dev);
    int i;

    /* free all dma slots */
    for (i = 0; i < ATA_DMA_SLOTS; i++) {
	struct ata_dmaslot *slot = &ch->dma.slot[i];

	if (slot->sg_bus) {
            bus_dmamap_unload(slot->sg_tag, slot->sg_map);
            slot->sg_bus = 0;
	}
	if (slot->sg) {
            bus_dmamem_free(slot->sg_tag, slot->sg, slot->sg_map);
            slot->sg = NULL;
	}
	if (slot->data_map) {
            bus_dmamap_destroy(slot->data_tag, slot->data_map);
            slot->data_map = NULL;
	}
	if (slot->sg_tag) {
            bus_dma_tag_destroy(slot->sg_tag);
            slot->sg_tag = NULL;
	}
	if (slot->data_tag) {
            bus_dma_tag_destroy(slot->data_tag);
            slot->data_tag = NULL;
	}
    }
}