#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  req_prod_pvt; } ;
struct xbd_softc {int xbd_max_request_segments; int xbd_max_request_indirectpages; int /*<<< orphan*/  xbd_io_dmat; int /*<<< orphan*/  xbd_dev; scalar_t__ xbd_disk; TYPE_4__ xbd_ring; } ;
struct xbd_command {scalar_t__ cm_operation; int cm_nseg; int cm_flags; int /*<<< orphan*/  cm_gref_head; int /*<<< orphan*/  cm_map; int /*<<< orphan*/  cm_indirectionrefs; int /*<<< orphan*/  cm_indirectionpages; int /*<<< orphan*/  cm_sg_refs; int /*<<< orphan*/  cm_sector_number; int /*<<< orphan*/  cm_id; TYPE_3__* cm_bp; struct xbd_softc* cm_sc; } ;
typedef  int /*<<< orphan*/  grant_ref_t ;
typedef  int /*<<< orphan*/  bus_dma_segment_t ;
typedef  void* blkif_vdev_t ;
struct TYPE_5__ {scalar_t__ operation; int nr_segments; int /*<<< orphan*/  seg; void* handle; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ blkif_request_t ;
struct TYPE_6__ {scalar_t__ indirect_op; int nr_segments; int /*<<< orphan*/  indirect_grefs; void* handle; int /*<<< orphan*/  sector_number; int /*<<< orphan*/  operation; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ blkif_request_indirect_t ;
struct TYPE_7__ {int /*<<< orphan*/  bio_error; } ;

/* Variables and functions */
 int BLKIF_MAX_SEGMENTS_PER_REQUEST ; 
 int /*<<< orphan*/  BLKIF_OP_INDIRECT ; 
 scalar_t__ BLKIF_OP_READ ; 
 scalar_t__ BLKIF_OP_WRITE ; 
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ RING_GET_REQUEST (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int XBDCF_ASYNC_MAPPING ; 
 int /*<<< orphan*/  XBD_Q_BUSY ; 
 int /*<<< orphan*/  biodone (TYPE_3__*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gnttab_free_grant_references (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xbd_enqueue_cm (struct xbd_command*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xbd_flush_requests (struct xbd_softc*) ; 
 int /*<<< orphan*/  xbd_free_command (struct xbd_command*) ; 
 int /*<<< orphan*/  xbd_mksegarray (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xenbus_get_otherend_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xbd_queue_cb(void *arg, bus_dma_segment_t *segs, int nsegs, int error)
{
	struct xbd_softc *sc;
	struct xbd_command *cm;
	int op;

	cm = arg;
	sc = cm->cm_sc;

	if (error) {
		cm->cm_bp->bio_error = EIO;
		biodone(cm->cm_bp);
		xbd_free_command(cm);
		return;
	}

	KASSERT(nsegs <= sc->xbd_max_request_segments,
	    ("Too many segments in a blkfront I/O"));

	if (nsegs <= BLKIF_MAX_SEGMENTS_PER_REQUEST) {
		blkif_request_t	*ring_req;

		/* Fill out a blkif_request_t structure. */
		ring_req = (blkif_request_t *)
		    RING_GET_REQUEST(&sc->xbd_ring, sc->xbd_ring.req_prod_pvt);
		sc->xbd_ring.req_prod_pvt++;
		ring_req->id = cm->cm_id;
		ring_req->operation = cm->cm_operation;
		ring_req->sector_number = cm->cm_sector_number;
		ring_req->handle = (blkif_vdev_t)(uintptr_t)sc->xbd_disk;
		ring_req->nr_segments = nsegs;
		cm->cm_nseg = nsegs;
		xbd_mksegarray(segs, nsegs, &cm->cm_gref_head,
		    xenbus_get_otherend_id(sc->xbd_dev),
		    cm->cm_operation == BLKIF_OP_WRITE,
		    cm->cm_sg_refs, ring_req->seg);
	} else {
		blkif_request_indirect_t *ring_req;

		/* Fill out a blkif_request_indirect_t structure. */
		ring_req = (blkif_request_indirect_t *)
		    RING_GET_REQUEST(&sc->xbd_ring, sc->xbd_ring.req_prod_pvt);
		sc->xbd_ring.req_prod_pvt++;
		ring_req->id = cm->cm_id;
		ring_req->operation = BLKIF_OP_INDIRECT;
		ring_req->indirect_op = cm->cm_operation;
		ring_req->sector_number = cm->cm_sector_number;
		ring_req->handle = (blkif_vdev_t)(uintptr_t)sc->xbd_disk;
		ring_req->nr_segments = nsegs;
		cm->cm_nseg = nsegs;
		xbd_mksegarray(segs, nsegs, &cm->cm_gref_head,
		    xenbus_get_otherend_id(sc->xbd_dev),
		    cm->cm_operation == BLKIF_OP_WRITE,
		    cm->cm_sg_refs, cm->cm_indirectionpages);
		memcpy(ring_req->indirect_grefs, &cm->cm_indirectionrefs,
		    sizeof(grant_ref_t) * sc->xbd_max_request_indirectpages);
	}

	if (cm->cm_operation == BLKIF_OP_READ)
		op = BUS_DMASYNC_PREREAD;
	else if (cm->cm_operation == BLKIF_OP_WRITE)
		op = BUS_DMASYNC_PREWRITE;
	else
		op = 0;
	bus_dmamap_sync(sc->xbd_io_dmat, cm->cm_map, op);

	gnttab_free_grant_references(cm->cm_gref_head);

	xbd_enqueue_cm(cm, XBD_Q_BUSY);

	/*
	 * If bus dma had to asynchronously call us back to dispatch
	 * this command, we are no longer executing in the context of 
	 * xbd_startio().  Thus we cannot rely on xbd_startio()'s call to
	 * xbd_flush_requests() to publish this command to the backend
	 * along with any other commands that it could batch.
	 */
	if ((cm->cm_flags & XBDCF_ASYNC_MAPPING) != 0)
		xbd_flush_requests(sc);

	return;
}