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
struct nvme_tracker {struct nvme_request* req; int /*<<< orphan*/  payload_dma_map; int /*<<< orphan*/  timer; } ;
struct TYPE_4__ {scalar_t__ cid; } ;
struct nvme_request {scalar_t__ retries; scalar_t__ type; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* cb_fn ) (int /*<<< orphan*/ ,struct nvme_completion*) ;TYPE_2__ cmd; } ;
struct nvme_qpair {int /*<<< orphan*/  lock; int /*<<< orphan*/  queued_req; TYPE_1__* ctrlr; int /*<<< orphan*/  free_tr; int /*<<< orphan*/  outstanding_tr; int /*<<< orphan*/  dma_tag_payload; int /*<<< orphan*/ ** act_tr; int /*<<< orphan*/  num_failures; int /*<<< orphan*/  num_retries; } ;
struct nvme_completion {size_t cid; } ;
typedef  scalar_t__ error_print_t ;
typedef  int boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  is_resetting; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 scalar_t__ ERROR_PRINT_ALL ; 
 scalar_t__ ERROR_PRINT_NO_RETRY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ NVME_REQUEST_NULL ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct nvme_request* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_INSERT_HEAD (int /*<<< orphan*/ *,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _nvme_qpair_submit_request (struct nvme_qpair*,struct nvme_request*) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_dmamap_unload (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int nvme_completion_is_error (struct nvme_completion*) ; 
 int nvme_completion_is_retry (struct nvme_completion*) ; 
 int /*<<< orphan*/  nvme_free_request (struct nvme_request*) ; 
 int /*<<< orphan*/  nvme_qpair_print_command (struct nvme_qpair*,TYPE_2__*) ; 
 int /*<<< orphan*/  nvme_qpair_print_completion (struct nvme_qpair*,struct nvme_completion*) ; 
 int /*<<< orphan*/  nvme_qpair_submit_tracker (struct nvme_qpair*,struct nvme_tracker*) ; 
 scalar_t__ nvme_retry_count ; 
 int /*<<< orphan*/  stailq ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct nvme_completion*) ; 
 int /*<<< orphan*/  tailq ; 

__attribute__((used)) static void
nvme_qpair_complete_tracker(struct nvme_qpair *qpair, struct nvme_tracker *tr,
    struct nvme_completion *cpl, error_print_t print_on_error)
{
	struct nvme_request	*req;
	boolean_t		retry, error, retriable;

	req = tr->req;
	error = nvme_completion_is_error(cpl);
	retriable = nvme_completion_is_retry(cpl);
	retry = error && retriable && req->retries < nvme_retry_count;
	if (retry)
		qpair->num_retries++;
	if (error && req->retries >= nvme_retry_count && retriable)
		qpair->num_failures++;

	if (error && (print_on_error == ERROR_PRINT_ALL ||
		(!retry && print_on_error == ERROR_PRINT_NO_RETRY))) {
		nvme_qpair_print_command(qpair, &req->cmd);
		nvme_qpair_print_completion(qpair, cpl);
	}

	qpair->act_tr[cpl->cid] = NULL;

	KASSERT(cpl->cid == req->cmd.cid, ("cpl cid does not match cmd cid\n"));

	if (req->cb_fn && !retry)
		req->cb_fn(req->cb_arg, cpl);

	mtx_lock(&qpair->lock);
	callout_stop(&tr->timer);

	if (retry) {
		req->retries++;
		nvme_qpair_submit_tracker(qpair, tr);
	} else {
		if (req->type != NVME_REQUEST_NULL) {
			bus_dmamap_sync(qpair->dma_tag_payload,
			    tr->payload_dma_map,
			    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
			bus_dmamap_unload(qpair->dma_tag_payload,
			    tr->payload_dma_map);
		}

		nvme_free_request(req);
		tr->req = NULL;

		TAILQ_REMOVE(&qpair->outstanding_tr, tr, tailq);
		TAILQ_INSERT_HEAD(&qpair->free_tr, tr, tailq);

		/*
		 * If the controller is in the middle of resetting, don't
		 *  try to submit queued requests here - let the reset logic
		 *  handle that instead.
		 */
		if (!STAILQ_EMPTY(&qpair->queued_req) &&
		    !qpair->ctrlr->is_resetting) {
			req = STAILQ_FIRST(&qpair->queued_req);
			STAILQ_REMOVE_HEAD(&qpair->queued_req, stailq);
			_nvme_qpair_submit_request(qpair, req);
		}
	}

	mtx_unlock(&qpair->lock);
}