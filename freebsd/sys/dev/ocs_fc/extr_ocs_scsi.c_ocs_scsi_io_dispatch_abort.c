#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  io_pending_lock; int /*<<< orphan*/  io_total_pending; int /*<<< orphan*/  io_pending_count; int /*<<< orphan*/  io_pending_list; } ;
typedef  TYPE_1__ ocs_xport_t ;
struct TYPE_9__ {TYPE_1__* xport; } ;
typedef  TYPE_2__ ocs_t ;
struct TYPE_10__ {scalar_t__ io_type; void* hw_cb; TYPE_2__* ocs; } ;
typedef  TYPE_3__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 scalar_t__ OCS_IO_TYPE_ABORT ; 
 int /*<<< orphan*/  ocs_assert (int,int) ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_check_pending (TYPE_2__*) ; 
 int /*<<< orphan*/  ocs_scsi_io_dispatch_no_hw_io (TYPE_3__*) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

int32_t
ocs_scsi_io_dispatch_abort(ocs_io_t *io, void *cb)
{
	ocs_t *ocs = io->ocs;
	ocs_xport_t *xport = ocs->xport;

	ocs_assert((io->io_type == OCS_IO_TYPE_ABORT), -1);
	io->hw_cb = cb;

	/*
	 * For aborts, we don't need a HW IO, but we still want to pass through
	 * the pending list to preserve ordering. Thus, if the pending list is
	 * not empty, add this abort to the pending list and process the pending list.
	 */
	ocs_lock(&xport->io_pending_lock);
		if (!ocs_list_empty(&xport->io_pending_list)) {
			ocs_list_add_tail(&xport->io_pending_list, io);
			ocs_unlock(&xport->io_pending_lock);
			ocs_atomic_add_return(&xport->io_pending_count, 1);
			ocs_atomic_add_return(&xport->io_total_pending, 1);

			/* process pending list */
			ocs_scsi_check_pending(ocs);
			return 0;
		}
	ocs_unlock(&xport->io_pending_lock);

	/* nothing on pending list, dispatch abort */
	return ocs_scsi_io_dispatch_no_hw_io(io);

}