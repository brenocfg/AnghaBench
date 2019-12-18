#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct a31dmac_channel {int /*<<< orphan*/  physaddr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void
a31dmac_dmamap_cb(void *priv, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct a31dmac_channel *ch;

	if (error != 0)
		return;

	ch = priv;
	ch->physaddr = segs[0].ds_addr;
}