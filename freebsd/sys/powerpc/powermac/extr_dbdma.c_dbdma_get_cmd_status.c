#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_5__ {TYPE_1__* sc_slots; int /*<<< orphan*/  sc_dmamap; int /*<<< orphan*/  sc_dmatag; } ;
typedef  TYPE_2__ dbdma_channel_t ;
struct TYPE_4__ {int /*<<< orphan*/  resCount; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 

uint16_t
dbdma_get_cmd_status(dbdma_channel_t *chan, int slot)
{

	bus_dmamap_sync(chan->sc_dmatag, chan->sc_dmamap, BUS_DMASYNC_POSTREAD);

	/*
	 * I really did mean to swap resCount and xferStatus here, to
	 * account for the quad-word little endian fields.
	 */
	return (le16toh(chan->sc_slots[slot].resCount));
}