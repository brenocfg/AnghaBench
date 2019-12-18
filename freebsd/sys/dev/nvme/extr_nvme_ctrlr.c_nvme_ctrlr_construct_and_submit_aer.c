#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  opc; } ;
struct nvme_request {TYPE_1__ cmd; int /*<<< orphan*/  timeout; } ;
struct nvme_controller {int dummy; } ;
struct nvme_async_event_request {struct nvme_request* req; struct nvme_controller* ctrlr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NVME_OPC_ASYNC_EVENT_REQUEST ; 
 struct nvme_request* nvme_allocate_request_null (int /*<<< orphan*/ ,struct nvme_async_event_request*) ; 
 int /*<<< orphan*/  nvme_ctrlr_async_event_cb ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_admin_request (struct nvme_controller*,struct nvme_request*) ; 

__attribute__((used)) static void
nvme_ctrlr_construct_and_submit_aer(struct nvme_controller *ctrlr,
    struct nvme_async_event_request *aer)
{
	struct nvme_request *req;

	aer->ctrlr = ctrlr;
	req = nvme_allocate_request_null(nvme_ctrlr_async_event_cb, aer);
	aer->req = req;

	/*
	 * Disable timeout here, since asynchronous event requests should by
	 *  nature never be timed out.
	 */
	req->timeout = FALSE;
	req->cmd.opc = NVME_OPC_ASYNC_EVENT_REQUEST;
	nvme_ctrlr_submit_admin_request(ctrlr, req);
}