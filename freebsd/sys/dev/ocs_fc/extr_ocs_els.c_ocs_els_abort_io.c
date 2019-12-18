#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* display_name; int send_abts; int /*<<< orphan*/  ref; struct TYPE_14__* io_to_abort; int /*<<< orphan*/  io_type; int /*<<< orphan*/  cmd_ini; struct TYPE_14__* node; struct TYPE_14__* ocs; int /*<<< orphan*/ * hio; int /*<<< orphan*/  io_alloc_failed_count; struct TYPE_14__* xport; } ;
typedef  TYPE_1__ ocs_xport_t ;
typedef  TYPE_1__ ocs_t ;
typedef  TYPE_1__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_IO_TYPE_ABORT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_els_abort_cb ; 
 TYPE_1__* ocs_io_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_io_free (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_log_debug (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ocs_ref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_io_dispatch_abort (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ocs_io_t *
ocs_els_abort_io(ocs_io_t *els, int send_abts)
{
	ocs_t *ocs;
	ocs_xport_t *xport;
	int32_t rc;
	ocs_io_t *abort_io = NULL;

	ocs_assert(els, NULL);
	ocs_assert(els->node, NULL);
	ocs_assert(els->node->ocs, NULL);

	ocs = els->node->ocs;
	ocs_assert(ocs->xport, NULL);
	xport = ocs->xport;

	/* take a reference on IO being aborted */
	if ((ocs_ref_get_unless_zero(&els->ref) == 0)) {
		/* command no longer active */
		ocs_log_debug(ocs, "els no longer active\n");
		return NULL;
	}

	/* allocate IO structure to send abort */
	abort_io = ocs_io_alloc(ocs);
	if (abort_io == NULL) {
		ocs_atomic_add_return(&xport->io_alloc_failed_count, 1);
	} else {
		ocs_assert(abort_io->hio == NULL, NULL);

		/* set generic fields */
		abort_io->ocs = ocs;
		abort_io->node = els->node;
		abort_io->cmd_ini = TRUE;

		/* set type and ABORT-specific fields */
		abort_io->io_type = OCS_IO_TYPE_ABORT;
		abort_io->display_name = "abort_els";
		abort_io->io_to_abort = els;
		abort_io->send_abts = send_abts;

		/* now dispatch IO */
		if ((rc = ocs_scsi_io_dispatch_abort(abort_io, ocs_els_abort_cb))) {
			ocs_log_err(ocs, "ocs_scsi_io_dispatch failed: %d\n", rc);
			ocs_io_free(ocs, abort_io);
			abort_io = NULL;
		}
	}

	/* if something failed, put reference on ELS to abort */
	if (abort_io == NULL) {
		ocs_ref_put(&els->ref); /* ocs_ref_get(): same function */
	}
	return abort_io;
}