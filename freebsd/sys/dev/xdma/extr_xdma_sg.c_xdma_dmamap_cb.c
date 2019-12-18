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
struct seg_load_request {int error; int nsegs; struct bus_dma_segment* seg; } ;
struct bus_dma_segment {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
struct TYPE_3__ {int /*<<< orphan*/  ds_len; int /*<<< orphan*/  ds_addr; } ;
typedef  TYPE_1__ bus_dma_segment_t ;

/* Variables and functions */

__attribute__((used)) static void
xdma_dmamap_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct seg_load_request *slr;
	struct bus_dma_segment *seg;
	int i;

	slr = arg;
	seg = slr->seg;

	if (error != 0) {
		slr->error = error;
		return;
	}

	slr->nsegs = nsegs;

	for (i = 0; i < nsegs; i++) {
		seg[i].ds_addr = segs[i].ds_addr;
		seg[i].ds_len = segs[i].ds_len;
	}
}