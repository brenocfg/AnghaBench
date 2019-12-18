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
typedef  int uint64_t ;
struct nvme_request {int /*<<< orphan*/  cmd; } ;
struct nvme_namespace {int /*<<< orphan*/  ctrlr; int /*<<< orphan*/  id; } ;
struct bio {int bio_offset; int bio_bcount; } ;
typedef  int /*<<< orphan*/  nvme_cb_fn_t ;

/* Variables and functions */
 int ENOMEM ; 
 struct nvme_request* nvme_allocate_request_bio (struct bio*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  nvme_ctrlr_submit_io_request (int /*<<< orphan*/ ,struct nvme_request*) ; 
 int nvme_ns_get_sector_size (struct nvme_namespace*) ; 
 int /*<<< orphan*/  nvme_ns_write_cmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 

int
nvme_ns_cmd_write_bio(struct nvme_namespace *ns, struct bio *bp,
    nvme_cb_fn_t cb_fn, void *cb_arg)
{
	struct nvme_request	*req;
	uint64_t		lba;
	uint64_t		lba_count;

	req = nvme_allocate_request_bio(bp, cb_fn, cb_arg);

	if (req == NULL)
		return (ENOMEM);
	lba = bp->bio_offset / nvme_ns_get_sector_size(ns);
	lba_count = bp->bio_bcount / nvme_ns_get_sector_size(ns);
	nvme_ns_write_cmd(&req->cmd, ns->id, lba, lba_count);

	nvme_ctrlr_submit_io_request(ns->ctrlr, req);

	return (0);
}