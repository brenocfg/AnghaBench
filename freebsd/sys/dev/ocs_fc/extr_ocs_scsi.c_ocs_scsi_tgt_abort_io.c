#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  io_alloc_failed_count; } ;
typedef  TYPE_1__ ocs_xport_t ;
struct TYPE_11__ {char* display_name; int /*<<< orphan*/  ref; void* abort_cb_arg; int /*<<< orphan*/  abort_cb; int /*<<< orphan*/  send_abts; struct TYPE_11__* io_to_abort; int /*<<< orphan*/  io_type; struct TYPE_11__* node; int /*<<< orphan*/  cmd_tgt; int /*<<< orphan*/ * hio; TYPE_1__* xport; struct TYPE_11__* ocs; } ;
typedef  TYPE_2__ ocs_t ;
typedef  int /*<<< orphan*/  ocs_scsi_io_cb_t ;
typedef  TYPE_2__ ocs_io_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OCS_IO_TYPE_ABORT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 TYPE_2__* ocs_io_alloc (TYPE_2__*) ; 
 scalar_t__ ocs_ref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_put (int /*<<< orphan*/ *) ; 
 int ocs_scsi_io_dispatch_abort (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_target_abort_cb ; 
 int /*<<< orphan*/  scsi_io_printf (TYPE_2__*,char*) ; 

int32_t
ocs_scsi_tgt_abort_io(ocs_io_t *io, ocs_scsi_io_cb_t cb, void *arg)
{
	ocs_t *ocs;
	ocs_xport_t *xport;
	int32_t rc;

	ocs_io_t *abort_io = NULL;
	ocs_assert(io, -1);
	ocs_assert(io->node, -1);
	ocs_assert(io->ocs, -1);

	ocs = io->ocs;
	xport = ocs->xport;

	/* take a reference on IO being aborted */
	if ((ocs_ref_get_unless_zero(&io->ref) == 0)) {
		/* command no longer active */
		scsi_io_printf(io, "command no longer active\n");
		return -1;
	}

	/*
	 * allocate a new IO to send the abort request. Use ocs_io_alloc() directly, as
	 * we need an IO object that will not fail allocation due to allocations being
	 * disabled (in ocs_scsi_io_alloc())
	 */
	abort_io = ocs_io_alloc(ocs);
	if (abort_io == NULL) {
		ocs_atomic_add_return(&xport->io_alloc_failed_count, 1);
		ocs_ref_put(&io->ref); /* ocs_ref_get(): same function */
		return -1;
	}

	/* Save the target server callback and argument */
	ocs_assert(abort_io->hio == NULL, -1);

	/* set generic fields */
	abort_io->cmd_tgt = TRUE;
	abort_io->node = io->node;

	/* set type and abort-specific fields */
	abort_io->io_type = OCS_IO_TYPE_ABORT;
	abort_io->display_name = "tgt_abort";
	abort_io->io_to_abort = io;
	abort_io->send_abts = FALSE;
	abort_io->abort_cb = cb;
	abort_io->abort_cb_arg = arg;

	/* now dispatch IO */
	rc = ocs_scsi_io_dispatch_abort(abort_io, ocs_target_abort_cb);
	if (rc) {
		ocs_ref_put(&io->ref); /* ocs_ref_get(): same function */
	}
	return rc;
}