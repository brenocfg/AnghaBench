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
struct nvme_tracker {size_t cid; int /*<<< orphan*/  timer; struct nvme_request* req; } ;
struct TYPE_2__ {size_t cid; } ;
struct nvme_request {TYPE_1__ cmd; scalar_t__ timeout; } ;
struct nvme_qpair {size_t sq_tail; size_t num_entries; int /*<<< orphan*/  num_cmds; int /*<<< orphan*/  sq_tdbl_off; struct nvme_controller* ctrlr; int /*<<< orphan*/  queuemem_map; int /*<<< orphan*/  dma_tag; int /*<<< orphan*/ * cmd; int /*<<< orphan*/  cpu; struct nvme_tracker** act_tr; int /*<<< orphan*/  lock; } ;
struct nvme_controller {int timeout_period; int /*<<< orphan*/  bus_handle; int /*<<< orphan*/  bus_tag; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bus_space_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  callout_reset_on (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct nvme_tracker*,int /*<<< orphan*/ ) ; 
 int hz ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvme_timeout ; 
 int /*<<< orphan*/  wmb () ; 

void
nvme_qpair_submit_tracker(struct nvme_qpair *qpair, struct nvme_tracker *tr)
{
	struct nvme_request	*req;
	struct nvme_controller	*ctrlr;

	mtx_assert(&qpair->lock, MA_OWNED);

	req = tr->req;
	req->cmd.cid = tr->cid;
	qpair->act_tr[tr->cid] = tr;
	ctrlr = qpair->ctrlr;

	if (req->timeout)
		callout_reset_on(&tr->timer, ctrlr->timeout_period * hz,
		    nvme_timeout, tr, qpair->cpu);

	/* Copy the command from the tracker to the submission queue. */
	memcpy(&qpair->cmd[qpair->sq_tail], &req->cmd, sizeof(req->cmd));

	if (++qpair->sq_tail == qpair->num_entries)
		qpair->sq_tail = 0;

	bus_dmamap_sync(qpair->dma_tag, qpair->queuemem_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
#ifndef __powerpc__
	/*
	 * powerpc's bus_dmamap_sync() already includes a heavyweight sync, but
	 * no other archs do.
	 */
	wmb();
#endif

	bus_space_write_4(qpair->ctrlr->bus_tag, qpair->ctrlr->bus_handle,
	    qpair->sq_tdbl_off, qpair->sq_tail);
	qpair->num_cmds++;
}