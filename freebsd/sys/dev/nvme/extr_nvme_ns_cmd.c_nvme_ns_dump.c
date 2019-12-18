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
typedef  size_t uint64_t ;
struct nvme_command {int dummy; } ;
struct nvme_request {int /*<<< orphan*/ * qpair; struct nvme_command cmd; } ;
struct nvme_namespace {int /*<<< orphan*/  ctrlr; int /*<<< orphan*/  id; } ;
struct nvme_completion_poll_status {scalar_t__ done; } ;
typedef  size_t off_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENOMEM ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NVD_DUMP_TIMEOUT ; 
 struct nvme_request* nvme_allocate_request_vaddr (void*,size_t,int /*<<< orphan*/ ,struct nvme_completion_poll_status*) ; 
 int /*<<< orphan*/  nvme_completion_poll_cb ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_io_request (int /*<<< orphan*/ ,struct nvme_request*) ; 
 int /*<<< orphan*/  nvme_ns_flush_cmd (struct nvme_command*,int /*<<< orphan*/ ) ; 
 size_t nvme_ns_get_sector_size (struct nvme_namespace*) ; 
 int /*<<< orphan*/  nvme_ns_write_cmd (struct nvme_command*,int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  nvme_qpair_process_completions (int /*<<< orphan*/ *) ; 

int
nvme_ns_dump(struct nvme_namespace *ns, void *virt, off_t offset, size_t len)
{
	struct nvme_completion_poll_status status;
	struct nvme_request *req;
	struct nvme_command *cmd;
	uint64_t lba, lba_count;
	int i;

	status.done = FALSE;
	req = nvme_allocate_request_vaddr(virt, len, nvme_completion_poll_cb,
	    &status);
	if (req == NULL)
		return (ENOMEM);

	cmd = &req->cmd;

	if (len > 0) {
		lba = offset / nvme_ns_get_sector_size(ns);
		lba_count = len / nvme_ns_get_sector_size(ns);
		nvme_ns_write_cmd(cmd, ns->id, lba, lba_count);
	} else
		nvme_ns_flush_cmd(cmd, ns->id);

	nvme_ctrlr_submit_io_request(ns->ctrlr, req);
	if (req->qpair == NULL)
		return (ENXIO);

	i = 0;
	while ((i++ < NVD_DUMP_TIMEOUT) && (status.done == FALSE)) {
		DELAY(5);
		nvme_qpair_process_completions(req->qpair);
	}

	/*
	 * Normally, when using the polling interface, we can't return a
	 * timeout error because we don't know when the completion routines
	 * will be called if the command later completes. However, in this
	 * case we're running a system dump, so all interrupts are turned
	 * off, the scheduler isn't running so there's nothing to complete
	 * the transaction.
	 */
	if (status.done == FALSE)
		return (ETIMEDOUT);

	return (0);
}