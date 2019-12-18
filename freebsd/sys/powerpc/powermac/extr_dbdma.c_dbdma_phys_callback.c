#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sc_slots_pa; } ;
typedef  TYPE_1__ dbdma_channel_t ;
struct TYPE_6__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHAN_CMDPTR ; 
 int /*<<< orphan*/  dbdma_write_reg (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dbdma_phys_callback(void *chan, bus_dma_segment_t *segs, int nsegs, int error)
{
	dbdma_channel_t *channel = (dbdma_channel_t *)(chan);

	channel->sc_slots_pa = segs[0].ds_addr;
	dbdma_write_reg(channel, CHAN_CMDPTR, channel->sc_slots_pa);
}