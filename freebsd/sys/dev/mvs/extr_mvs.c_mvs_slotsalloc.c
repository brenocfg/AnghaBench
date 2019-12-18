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
struct TYPE_4__ {int /*<<< orphan*/  data_map; } ;
struct mvs_slot {int slot; TYPE_2__ dma; int /*<<< orphan*/  timeout; int /*<<< orphan*/ * ccb; int /*<<< orphan*/  state; int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  data_tag; } ;
struct mvs_channel {int /*<<< orphan*/  dev; TYPE_1__ dma; int /*<<< orphan*/  mtx; struct mvs_slot* slot; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int MVS_MAX_SLOTS ; 
 int /*<<< orphan*/  MVS_SLOT_EMPTY ; 
 scalar_t__ bus_dmamap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct mvs_slot*,int) ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mvs_channel* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
mvs_slotsalloc(device_t dev)
{
	struct mvs_channel *ch = device_get_softc(dev);
	int i;

	/* Alloc and setup command/dma slots */
	bzero(ch->slot, sizeof(ch->slot));
	for (i = 0; i < MVS_MAX_SLOTS; i++) {
		struct mvs_slot *slot = &ch->slot[i];

		slot->dev = dev;
		slot->slot = i;
		slot->state = MVS_SLOT_EMPTY;
		slot->ccb = NULL;
		callout_init_mtx(&slot->timeout, &ch->mtx, 0);

		if (bus_dmamap_create(ch->dma.data_tag, 0, &slot->dma.data_map))
			device_printf(ch->dev, "FAILURE - create data_map\n");
	}
}