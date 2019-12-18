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
struct TYPE_2__ {int /*<<< orphan*/ * workrq_tag; int /*<<< orphan*/ * workrq; scalar_t__ workrq_bus; int /*<<< orphan*/  workrq_map; int /*<<< orphan*/ * workrp_tag; int /*<<< orphan*/ * workrp; scalar_t__ workrp_bus; int /*<<< orphan*/  workrp_map; int /*<<< orphan*/ * data_tag; } ;
struct mvs_channel {TYPE_1__ dma; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_dma_tag_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mvs_dmafini(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);

	if (ch->dma.data_tag) {
		bus_dma_tag_destroy(ch->dma.data_tag);
		ch->dma.data_tag = NULL;
	}
	if (ch->dma.workrp_bus) {
		bus_dmamap_unload(ch->dma.workrp_tag, ch->dma.workrp_map);
		bus_dmamem_free(ch->dma.workrp_tag,
		    ch->dma.workrp, ch->dma.workrp_map);
		ch->dma.workrp_bus = 0;
		ch->dma.workrp = NULL;
	}
	if (ch->dma.workrp_tag) {
		bus_dma_tag_destroy(ch->dma.workrp_tag);
		ch->dma.workrp_tag = NULL;
	}
	if (ch->dma.workrq_bus) {
		bus_dmamap_unload(ch->dma.workrq_tag, ch->dma.workrq_map);
		bus_dmamem_free(ch->dma.workrq_tag,
		    ch->dma.workrq, ch->dma.workrq_map);
		ch->dma.workrq_bus = 0;
		ch->dma.workrq = NULL;
	}
	if (ch->dma.workrq_tag) {
		bus_dma_tag_destroy(ch->dma.workrq_tag);
		ch->dma.workrq_tag = NULL;
	}
}