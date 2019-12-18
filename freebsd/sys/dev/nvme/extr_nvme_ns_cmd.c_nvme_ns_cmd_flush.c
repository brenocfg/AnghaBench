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
struct nvme_request {int /*<<< orphan*/  cmd; } ;
struct nvme_namespace {int /*<<< orphan*/  ctrlr; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct nvme_request* nvme_allocate_request_null (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_io_request (int /*<<< orphan*/ ,struct nvme_request*) ; 
 int /*<<< orphan*/  nvme_ns_flush_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
nvme_ns_cmd_flush(struct nvme_namespace *ns, nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request	*req;

	req = nvme_allocate_request_null(cb_fn, cb_arg);

	if (req == NULL)
		return (ENOMEM);

	nvme_ns_flush_cmd(&req->cmd, ns->id);
	nvme_ctrlr_submit_io_request(ns->ctrlr, req);

	return (0);
}