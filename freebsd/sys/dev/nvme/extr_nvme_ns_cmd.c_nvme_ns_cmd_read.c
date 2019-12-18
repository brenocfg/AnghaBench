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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct nvme_request {int /*<<< orphan*/  cmd; } ;
struct nvme_namespace {int /*<<< orphan*/  ctrlr; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct nvme_request* nvme_allocate_request_vaddr (void*,int,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_io_request (int /*<<< orphan*/ ,struct nvme_request*) ; 
 int nvme_ns_get_sector_size (struct nvme_namespace*) ; 
 int /*<<< orphan*/  nvme_ns_read_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int
nvme_ns_cmd_read(struct nvme_namespace *ns, void *payload, uint64_t lba,
    uint32_t lba_count, nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request	*req;

	req = nvme_allocate_request_vaddr(payload,
	    lba_count*nvme_ns_get_sector_size(ns), cb_fn, cb_arg);

	if (req == NULL)
		return (ENOMEM);

	nvme_ns_read_cmd(&req->cmd, ns->id, lba, lba_count);

	nvme_ctrlr_submit_io_request(ns->ctrlr, req);

	return (0);
}