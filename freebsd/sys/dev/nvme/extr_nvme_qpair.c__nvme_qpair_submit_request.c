#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvme_tracker {int /*<<< orphan*/  payload_dma_map; TYPE_2__* qpair; struct nvme_request* req; } ;
struct TYPE_6__ {int /*<<< orphan*/  payload; TYPE_5__* bio; } ;
struct nvme_request {int type; TYPE_1__ u; int /*<<< orphan*/  payload_size; struct nvme_qpair* qpair; } ;
struct nvme_qpair {int /*<<< orphan*/  lock; TYPE_3__* ctrlr; int /*<<< orphan*/  outstanding_tr; int /*<<< orphan*/  free_tr; int /*<<< orphan*/  queued_req; int /*<<< orphan*/  is_enabled; } ;
typedef  int /*<<< orphan*/  intmax_t ;
struct TYPE_9__ {int /*<<< orphan*/  bio_bcount; } ;
struct TYPE_8__ {int /*<<< orphan*/  max_xfer_size; scalar_t__ is_failed; } ;
struct TYPE_7__ {int /*<<< orphan*/  dma_tag_payload; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_NOT_RETRY ; 
 int /*<<< orphan*/  ERROR_PRINT_ALL ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
#define  NVME_REQUEST_BIO 131 
#define  NVME_REQUEST_CCB 130 
#define  NVME_REQUEST_NULL 129 
#define  NVME_REQUEST_VADDR 128 
 int /*<<< orphan*/  NVME_SCT_GENERIC ; 
 int /*<<< orphan*/  NVME_SC_DATA_TRANSFER_ERROR ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nvme_request*,int /*<<< orphan*/ ) ; 
 struct nvme_tracker* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_bio (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int bus_dmamap_load_ccb (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_ctrlr_post_failed_request (TYPE_3__*,struct nvme_request*) ; 
 int /*<<< orphan*/  nvme_payload_map ; 
 int /*<<< orphan*/  nvme_printf (TYPE_3__*,char*,int) ; 
 int /*<<< orphan*/  nvme_qpair_manual_complete_tracker (struct nvme_qpair*,struct nvme_tracker*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_qpair_submit_tracker (TYPE_2__*,struct nvme_tracker*) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  stailq ; 
 int /*<<< orphan*/  tailq ; 

__attribute__((used)) static void
_nvme_qpair_submit_request(struct nvme_qpair *qpair, struct nvme_request *req)
{
	struct nvme_tracker	*tr;
	int			err = 0;

	mtx_assert(&qpair->lock, MA_OWNED);

	tr = TAILQ_FIRST(&qpair->free_tr);
	req->qpair = qpair;

	if (tr == NULL || !qpair->is_enabled) {
		/*
		 * No tracker is available, or the qpair is disabled due to
		 *  an in-progress controller-level reset or controller
		 *  failure.
		 */

		if (qpair->ctrlr->is_failed) {
			/*
			 * The controller has failed.  Post the request to a
			 *  task where it will be aborted, so that we do not
			 *  invoke the request's callback in the context
			 *  of the submission.
			 */
			nvme_ctrlr_post_failed_request(qpair->ctrlr, req);
		} else {
			/*
			 * Put the request on the qpair's request queue to be
			 *  processed when a tracker frees up via a command
			 *  completion or when the controller reset is
			 *  completed.
			 */
			STAILQ_INSERT_TAIL(&qpair->queued_req, req, stailq);
		}
		return;
	}

	TAILQ_REMOVE(&qpair->free_tr, tr, tailq);
	TAILQ_INSERT_TAIL(&qpair->outstanding_tr, tr, tailq);
	tr->req = req;

	switch (req->type) {
	case NVME_REQUEST_VADDR:
		KASSERT(req->payload_size <= qpair->ctrlr->max_xfer_size,
		    ("payload_size (%d) exceeds max_xfer_size (%d)\n",
		    req->payload_size, qpair->ctrlr->max_xfer_size));
		err = bus_dmamap_load(tr->qpair->dma_tag_payload,
		    tr->payload_dma_map, req->u.payload, req->payload_size,
		    nvme_payload_map, tr, 0);
		if (err != 0)
			nvme_printf(qpair->ctrlr,
			    "bus_dmamap_load returned 0x%x!\n", err);
		break;
	case NVME_REQUEST_NULL:
		nvme_qpair_submit_tracker(tr->qpair, tr);
		break;
	case NVME_REQUEST_BIO:
		KASSERT(req->u.bio->bio_bcount <= qpair->ctrlr->max_xfer_size,
		    ("bio->bio_bcount (%jd) exceeds max_xfer_size (%d)\n",
		    (intmax_t)req->u.bio->bio_bcount,
		    qpair->ctrlr->max_xfer_size));
		err = bus_dmamap_load_bio(tr->qpair->dma_tag_payload,
		    tr->payload_dma_map, req->u.bio, nvme_payload_map, tr, 0);
		if (err != 0)
			nvme_printf(qpair->ctrlr,
			    "bus_dmamap_load_bio returned 0x%x!\n", err);
		break;
	case NVME_REQUEST_CCB:
		err = bus_dmamap_load_ccb(tr->qpair->dma_tag_payload,
		    tr->payload_dma_map, req->u.payload,
		    nvme_payload_map, tr, 0);
		if (err != 0)
			nvme_printf(qpair->ctrlr,
			    "bus_dmamap_load_ccb returned 0x%x!\n", err);
		break;
	default:
		panic("unknown nvme request type 0x%x\n", req->type);
		break;
	}

	if (err != 0) {
		/*
		 * The dmamap operation failed, so we manually fail the
		 *  tracker here with DATA_TRANSFER_ERROR status.
		 *
		 * nvme_qpair_manual_complete_tracker must not be called
		 *  with the qpair lock held.
		 */
		mtx_unlock(&qpair->lock);
		nvme_qpair_manual_complete_tracker(qpair, tr, NVME_SCT_GENERIC,
		    NVME_SC_DATA_TRANSFER_ERROR, DO_NOT_RETRY, ERROR_PRINT_ALL);
		mtx_lock(&qpair->lock);
	}
}