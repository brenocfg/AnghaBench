#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nvme_tracker {int dummy; } ;
struct nvme_request {int dummy; } ;
struct nvme_qpair {int /*<<< orphan*/  lock; int /*<<< orphan*/  ctrlr; int /*<<< orphan*/  outstanding_tr; int /*<<< orphan*/  queued_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  DO_NOT_RETRY ; 
 int /*<<< orphan*/  ERROR_PRINT_ALL ; 
 int /*<<< orphan*/  NVME_SCT_GENERIC ; 
 int /*<<< orphan*/  NVME_SC_ABORTED_BY_REQUEST ; 
 int /*<<< orphan*/  STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct nvme_request* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 struct nvme_tracker* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  nvme_qpair_manual_complete_request (struct nvme_qpair*,struct nvme_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_qpair_manual_complete_tracker (struct nvme_qpair*,struct nvme_tracker*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stailq ; 

void
nvme_qpair_fail(struct nvme_qpair *qpair)
{
	struct nvme_tracker		*tr;
	struct nvme_request		*req;

	if (!mtx_initialized(&qpair->lock))
		return;

	mtx_lock(&qpair->lock);

	while (!STAILQ_EMPTY(&qpair->queued_req)) {
		req = STAILQ_FIRST(&qpair->queued_req);
		STAILQ_REMOVE_HEAD(&qpair->queued_req, stailq);
		nvme_printf(qpair->ctrlr, "failing queued i/o\n");
		mtx_unlock(&qpair->lock);
		nvme_qpair_manual_complete_request(qpair, req, NVME_SCT_GENERIC,
		    NVME_SC_ABORTED_BY_REQUEST);
		mtx_lock(&qpair->lock);
	}

	/* Manually abort each outstanding I/O. */
	while (!TAILQ_EMPTY(&qpair->outstanding_tr)) {
		tr = TAILQ_FIRST(&qpair->outstanding_tr);
		/*
		 * Do not remove the tracker.  The abort_tracker path will
		 *  do that for us.
		 */
		nvme_printf(qpair->ctrlr, "failing outstanding i/o\n");
		mtx_unlock(&qpair->lock);
		nvme_qpair_manual_complete_tracker(qpair, tr, NVME_SCT_GENERIC,
		    NVME_SC_ABORTED_BY_REQUEST, DO_NOT_RETRY, ERROR_PRINT_ALL);
		mtx_lock(&qpair->lock);
	}

	mtx_unlock(&qpair->lock);
}