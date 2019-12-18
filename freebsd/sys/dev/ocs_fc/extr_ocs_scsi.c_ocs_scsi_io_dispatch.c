#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  io_pending_count; int /*<<< orphan*/  io_total_pending; int /*<<< orphan*/  io_pending_lock; int /*<<< orphan*/  io_pending_list; } ;
typedef  TYPE_1__ ocs_xport_t ;
struct TYPE_10__ {int /*<<< orphan*/  hw; TYPE_1__* xport; } ;
typedef  TYPE_2__ ocs_t ;
struct TYPE_11__ {scalar_t__ io_type; TYPE_2__* ocs; scalar_t__ low_latency; int /*<<< orphan*/ * hio; void* hw_cb; scalar_t__ cmd_ini; scalar_t__ cmd_tgt; } ;
typedef  TYPE_3__ ocs_io_t ;
typedef  int /*<<< orphan*/  ocs_hw_io_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ OCS_IO_TYPE_ABORT ; 
 int /*<<< orphan*/  ocs_assert (int,int) ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ocs_hw_io_alloc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_list_add_head (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_check_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_scsi_io_dispatch_hw_io (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

int32_t
ocs_scsi_io_dispatch(ocs_io_t *io, void *cb)
{
	ocs_hw_io_t *hio;
	ocs_t *ocs = io->ocs;
	ocs_xport_t *xport = ocs->xport;

	ocs_assert(io->cmd_tgt || io->cmd_ini, -1);
	ocs_assert((io->io_type != OCS_IO_TYPE_ABORT), -1);
	io->hw_cb = cb;

	/*
	 * if this IO already has a HW IO, then this is either not the first phase of
	 * the IO. Send it to the HW.
	 */
	if (io->hio != NULL) {
		return ocs_scsi_io_dispatch_hw_io(io, io->hio);
	}

	/*
	 * We don't already have a HW IO associated with the IO. First check
	 * the pending list. If not empty, add IO to the tail and process the
	 * pending list.
	 */
	ocs_lock(&xport->io_pending_lock);
		if (!ocs_list_empty(&xport->io_pending_list)) {
			/*
			 * If this is a low latency request, the put at the front of the IO pending
			 * queue, otherwise put it at the end of the queue.
			 */
			if (io->low_latency) {
				ocs_list_add_head(&xport->io_pending_list, io);
			} else {
				ocs_list_add_tail(&xport->io_pending_list, io);
			}
			ocs_unlock(&xport->io_pending_lock);
			ocs_atomic_add_return(&xport->io_pending_count, 1);
			ocs_atomic_add_return(&xport->io_total_pending, 1);

			/* process pending list */
			ocs_scsi_check_pending(ocs);
			return 0;
		}
	ocs_unlock(&xport->io_pending_lock);

	/*
	 * We don't have a HW IO associated with the IO and there's nothing
	 * on the pending list. Attempt to allocate a HW IO and dispatch it.
	 */
	hio = ocs_hw_io_alloc(&io->ocs->hw);
	if (hio == NULL) {

		/* Couldn't get a HW IO. Save this IO on the pending list */
		ocs_lock(&xport->io_pending_lock);
			ocs_list_add_tail(&xport->io_pending_list, io);
		ocs_unlock(&xport->io_pending_lock);

		ocs_atomic_add_return(&xport->io_total_pending, 1);
		ocs_atomic_add_return(&xport->io_pending_count, 1);
		return 0;
	}

	/* We successfully allocated a HW IO; dispatch to HW */
	return ocs_scsi_io_dispatch_hw_io(io, hio);
}