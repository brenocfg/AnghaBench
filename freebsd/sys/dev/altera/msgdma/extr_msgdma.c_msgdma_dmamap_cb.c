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
struct msgdma_channel {int map_err; size_t map_descr; TYPE_1__* descs_phys; } ;
struct TYPE_5__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_2__ bus_dma_segment_t ;
struct TYPE_4__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dprintf (char*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msgdma_dmamap_cb(void *arg, bus_dma_segment_t *segs, int nseg, int err)
{
	struct msgdma_channel *chan;

	chan = (struct msgdma_channel *)arg;
	KASSERT(chan != NULL, ("xchan is NULL"));

	if (err) {
		chan->map_err = 1;
		return;
	}

	chan->descs_phys[chan->map_descr].ds_addr = segs[0].ds_addr;
	chan->descs_phys[chan->map_descr].ds_len = segs[0].ds_len;

	dprintf("map desc %d: descs phys %lx len %ld\n",
	    chan->map_descr, segs[0].ds_addr, segs[0].ds_len);
}