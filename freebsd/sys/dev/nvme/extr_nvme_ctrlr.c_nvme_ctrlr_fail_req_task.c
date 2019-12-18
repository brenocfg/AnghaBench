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
struct nvme_request {int /*<<< orphan*/  qpair; } ;
struct nvme_controller {int /*<<< orphan*/  lock; int /*<<< orphan*/  fail_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVME_SCT_GENERIC ; 
 int /*<<< orphan*/  NVME_SC_ABORTED_BY_REQUEST ; 
 struct nvme_request* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvme_qpair_manual_complete_request (int /*<<< orphan*/ ,struct nvme_request*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stailq ; 

__attribute__((used)) static void
nvme_ctrlr_fail_req_task(void *arg, int pending)
{
	struct nvme_controller	*ctrlr = arg;
	struct nvme_request	*req;

	mtx_lock(&ctrlr->lock);
	while ((req = STAILQ_FIRST(&ctrlr->fail_req)) != NULL) {
		STAILQ_REMOVE_HEAD(&ctrlr->fail_req, stailq);
		mtx_unlock(&ctrlr->lock);
		nvme_qpair_manual_complete_request(req->qpair, req,
		    NVME_SCT_GENERIC, NVME_SC_ABORTED_BY_REQUEST);
		mtx_lock(&ctrlr->lock);
	}
	mtx_unlock(&ctrlr->lock);
}