#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xdma_controller_t ;
struct TYPE_10__ {int caps; int /*<<< orphan*/  queue_out; int /*<<< orphan*/  processing; int /*<<< orphan*/  dma_tag_bufs; int /*<<< orphan*/ * xdma; } ;
typedef  TYPE_2__ xdma_channel_t ;
struct xdma_transfer_status {int /*<<< orphan*/  transferred; int /*<<< orphan*/  error; } ;
struct TYPE_9__ {int /*<<< orphan*/  transferred; int /*<<< orphan*/  error; } ;
struct xchan_buf {scalar_t__ nsegs_left; scalar_t__ vaddr; int /*<<< orphan*/  map; } ;
struct xdma_request {scalar_t__ direction; scalar_t__ req_type; TYPE_1__ status; int /*<<< orphan*/  dst_addr; int /*<<< orphan*/  src_addr; struct xchan_buf buf; int /*<<< orphan*/  m; } ;
typedef  int /*<<< orphan*/  bus_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  QUEUE_OUT_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  QUEUE_OUT_UNLOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  QUEUE_PROC_LOCK (TYPE_2__*) ; 
 int /*<<< orphan*/  QUEUE_PROC_UNLOCK (TYPE_2__*) ; 
 struct xdma_request* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct xdma_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct xdma_request*,int /*<<< orphan*/ ) ; 
 int XCHAN_CAP_BOUNCE ; 
 int XCHAN_CAP_BUSDMA ; 
 int XCHAN_CAP_IOMMU ; 
 scalar_t__ XDMA_DEV_TO_MEM ; 
 scalar_t__ XDMA_MEM_TO_DEV ; 
 scalar_t__ XR_TYPE_MBUF ; 
 int /*<<< orphan*/  atomic_subtract_int (scalar_t__*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_copyback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  xdma_iommu_remove_entry (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xr_next ; 

void
xchan_seg_done(xdma_channel_t *xchan,
    struct xdma_transfer_status *st)
{
	struct xdma_request *xr;
	xdma_controller_t *xdma;
	struct xchan_buf *b;
	bus_addr_t addr;

	xdma = xchan->xdma;

	xr = TAILQ_FIRST(&xchan->processing);
	if (xr == NULL)
		panic("request not found\n");

	b = &xr->buf;

	atomic_subtract_int(&b->nsegs_left, 1);

	if (b->nsegs_left == 0) {
		if (xchan->caps & XCHAN_CAP_BUSDMA) {
			if (xr->direction == XDMA_MEM_TO_DEV)
				bus_dmamap_sync(xchan->dma_tag_bufs, b->map, 
				    BUS_DMASYNC_POSTWRITE);
			else
				bus_dmamap_sync(xchan->dma_tag_bufs, b->map, 
				    BUS_DMASYNC_POSTREAD);
			bus_dmamap_unload(xchan->dma_tag_bufs, b->map);
		} else if (xchan->caps & XCHAN_CAP_BOUNCE) {
			if (xr->req_type == XR_TYPE_MBUF &&
			    xr->direction == XDMA_DEV_TO_MEM)
				m_copyback(xr->m, 0, st->transferred,
				    (void *)xr->buf.vaddr);
		} else if (xchan->caps & XCHAN_CAP_IOMMU) {
			if (xr->direction == XDMA_MEM_TO_DEV)
				addr = xr->src_addr;
			else
				addr = xr->dst_addr;
			xdma_iommu_remove_entry(xchan, addr);
		}
		xr->status.error = st->error;
		xr->status.transferred = st->transferred;

		QUEUE_PROC_LOCK(xchan);
		TAILQ_REMOVE(&xchan->processing, xr, xr_next);
		QUEUE_PROC_UNLOCK(xchan);

		QUEUE_OUT_LOCK(xchan);
		TAILQ_INSERT_TAIL(&xchan->queue_out, xr, xr_next);
		QUEUE_OUT_UNLOCK(xchan);
	}
}