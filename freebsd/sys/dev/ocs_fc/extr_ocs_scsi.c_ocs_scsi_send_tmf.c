#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ ocs_scsi_tmf_cmd_e ;
typedef  int /*<<< orphan*/  ocs_scsi_sgl_t ;
typedef  int /*<<< orphan*/  ocs_scsi_rsp_io_cb_t ;
typedef  int /*<<< orphan*/  ocs_node_t ;
struct TYPE_8__ {char* display_name; int /*<<< orphan*/  ref; void* scsi_ini_cb_arg; int /*<<< orphan*/  scsi_ini_cb; int /*<<< orphan*/  send_abts; struct TYPE_8__* io_to_abort; int /*<<< orphan*/  io_type; } ;
typedef  TYPE_1__ ocs_io_t ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_IO_INITIATOR_READ ; 
 int /*<<< orphan*/  OCS_IO_TYPE_ABORT ; 
 scalar_t__ OCS_SCSI_TMF_ABORT_TASK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*,int) ; 
 scalar_t__ ocs_ref_get_unless_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_ref_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_scsi_abort_io_cb ; 
 int ocs_scsi_io_dispatch_abort (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int ocs_scsi_send_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  scsi_io_printf (TYPE_1__*,char*) ; 

int32_t
ocs_scsi_send_tmf(ocs_node_t *node, ocs_io_t *io, ocs_io_t *io_to_abort, uint64_t lun, ocs_scsi_tmf_cmd_e tmf,
	ocs_scsi_sgl_t *sgl, uint32_t sgl_count, uint32_t len, ocs_scsi_rsp_io_cb_t cb, void *arg)
{
	int32_t rc;
	ocs_assert(io, -1);

	if (tmf == OCS_SCSI_TMF_ABORT_TASK) {
		ocs_assert(io_to_abort, -1);

		/* take a reference on IO being aborted */
		if ((ocs_ref_get_unless_zero(&io_to_abort->ref) == 0)) {
			/* command no longer active */
			scsi_io_printf(io, "command no longer active\n");
			return -1;
		}
		/* generic io fields have already been populated */

		/* abort-specific fields */
		io->io_type = OCS_IO_TYPE_ABORT;
		io->display_name = "abort_task";
		io->io_to_abort = io_to_abort;
		io->send_abts = TRUE;
		io->scsi_ini_cb = cb;
		io->scsi_ini_cb_arg = arg;

		/* now dispatch IO */
		rc = ocs_scsi_io_dispatch_abort(io, ocs_scsi_abort_io_cb);
		if (rc) {
			scsi_io_printf(io, "Failed to dispatch abort\n");
			ocs_ref_put(&io->ref); /* ocs_ref_get(): same function */
		}
	} else {
		io->display_name = "tmf";
		rc = ocs_scsi_send_io(OCS_HW_IO_INITIATOR_READ, node, io, lun, tmf, NULL, 0, NULL,
				      sgl, sgl_count, len, 0, cb, arg);
	}

	return rc;
}