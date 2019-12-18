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
struct nvme_request {int dummy; } ;
struct nvme_controller {int /*<<< orphan*/  fail_req_task; int /*<<< orphan*/  taskqueue; int /*<<< orphan*/  lock; int /*<<< orphan*/  fail_req; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct nvme_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stailq ; 
 int /*<<< orphan*/  taskqueue_enqueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
nvme_ctrlr_post_failed_request(struct nvme_controller *ctrlr,
    struct nvme_request *req)
{

	mtx_lock(&ctrlr->lock);
	STAILQ_INSERT_TAIL(&ctrlr->fail_req, req, stailq);
	mtx_unlock(&ctrlr->lock);
	taskqueue_enqueue(ctrlr->taskqueue, &ctrlr->fail_req_task);
}