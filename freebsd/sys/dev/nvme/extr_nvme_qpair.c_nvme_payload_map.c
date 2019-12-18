#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct nvme_tracker {TYPE_4__* qpair; int /*<<< orphan*/  payload_dma_map; TYPE_2__* req; void** prp; scalar_t__ prp_bus_addr; } ;
struct TYPE_8__ {scalar_t__ ds_addr; } ;
typedef  TYPE_3__ bus_dma_segment_t ;
struct TYPE_9__ {int /*<<< orphan*/  dma_tag_payload; int /*<<< orphan*/  ctrlr; } ;
struct TYPE_6__ {void* prp2; void* prp1; } ;
struct TYPE_7__ {TYPE_1__ cmd; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 void* htole64 (scalar_t__) ; 
 int /*<<< orphan*/  nvme_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  nvme_qpair_submit_tracker (TYPE_4__*,struct nvme_tracker*) ; 

__attribute__((used)) static void
nvme_payload_map(void *arg, bus_dma_segment_t *seg, int nseg, int error)
{
	struct nvme_tracker 	*tr = arg;
	uint32_t		cur_nseg;

	/*
	 * If the mapping operation failed, return immediately.  The caller
	 *  is responsible for detecting the error status and failing the
	 *  tracker manually.
	 */
	if (error != 0) {
		nvme_printf(tr->qpair->ctrlr,
		    "nvme_payload_map err %d\n", error);
		return;
	}

	/*
	 * Note that we specified PAGE_SIZE for alignment and max
	 *  segment size when creating the bus dma tags.  So here
	 *  we can safely just transfer each segment to its
	 *  associated PRP entry.
	 */
	tr->req->cmd.prp1 = htole64(seg[0].ds_addr);

	if (nseg == 2) {
		tr->req->cmd.prp2 = htole64(seg[1].ds_addr);
	} else if (nseg > 2) {
		cur_nseg = 1;
		tr->req->cmd.prp2 = htole64((uint64_t)tr->prp_bus_addr);
		while (cur_nseg < nseg) {
			tr->prp[cur_nseg-1] =
			    htole64((uint64_t)seg[cur_nseg].ds_addr);
			cur_nseg++;
		}
	} else {
		/*
		 * prp2 should not be used by the controller
		 *  since there is only one segment, but set
		 *  to 0 just to be safe.
		 */
		tr->req->cmd.prp2 = 0;
	}

	bus_dmamap_sync(tr->qpair->dma_tag_payload, tr->payload_dma_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	nvme_qpair_submit_tracker(tr->qpair, tr);
}