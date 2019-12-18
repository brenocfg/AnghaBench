#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  active_ios_lock; int /*<<< orphan*/  active_ios; struct TYPE_13__* ocs; int /*<<< orphan*/  io_alloc_failed_count; int /*<<< orphan*/  io_alloc_enabled; struct TYPE_13__* xport; } ;
typedef  TYPE_1__ ocs_xport_t ;
typedef  TYPE_1__ ocs_t ;
typedef  int ocs_scsi_io_role_e ;
typedef  TYPE_1__ ocs_node_t ;
struct TYPE_14__ {char* display_name; void* cmd_tgt; void* cmd_ini; int /*<<< orphan*/  io_type; TYPE_1__* node; TYPE_1__* ocs; int /*<<< orphan*/ * hio; int /*<<< orphan*/  ref; } ;
typedef  TYPE_4__ ocs_io_t ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  OCS_IO_TYPE_IO ; 
#define  OCS_SCSI_IO_ROLE_ORIGINATOR 129 
#define  OCS_SCSI_IO_ROLE_RESPONDER 128 
 void* TRUE ; 
 int /*<<< orphan*/  _ocs_scsi_io_free ; 
 int /*<<< orphan*/  ocs_assert (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_atomic_add_return (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ocs_io_alloc (TYPE_1__*) ; 
 int /*<<< orphan*/  ocs_list_add_tail (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocs_log_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  ocs_ref_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ocs_unlock (int /*<<< orphan*/ *) ; 

ocs_io_t *
ocs_scsi_io_alloc(ocs_node_t *node, ocs_scsi_io_role_e role)
{
	ocs_t *ocs;
	ocs_xport_t *xport;
	ocs_io_t *io;

	ocs_assert(node, NULL);
	ocs_assert(node->ocs, NULL);

	ocs = node->ocs;
	ocs_assert(ocs->xport, NULL);
	xport = ocs->xport;

	ocs_lock(&node->active_ios_lock);

		if (!node->io_alloc_enabled) {
			ocs_unlock(&node->active_ios_lock);
			return NULL;
		}

		io = ocs_io_alloc(ocs);
		if (io == NULL) {
			ocs_atomic_add_return(&xport->io_alloc_failed_count, 1);
			ocs_unlock(&node->active_ios_lock);
			return NULL;
		}

		/* initialize refcount */
		ocs_ref_init(&io->ref, _ocs_scsi_io_free, io);

		if (io->hio != NULL) {
			ocs_log_err(node->ocs, "assertion failed: io->hio is not NULL\n");
			ocs_unlock(&node->active_ios_lock);
			return NULL;
		}

		/* set generic fields */
		io->ocs = ocs;
		io->node = node;

		/* set type and name */
		io->io_type = OCS_IO_TYPE_IO;
		io->display_name = "scsi_io";

		switch (role) {
		case OCS_SCSI_IO_ROLE_ORIGINATOR:
			io->cmd_ini = TRUE;
			io->cmd_tgt = FALSE;
			break;
		case OCS_SCSI_IO_ROLE_RESPONDER:
			io->cmd_ini = FALSE;
			io->cmd_tgt = TRUE;
			break;
		}

		/* Add to node's active_ios list */
		ocs_list_add_tail(&node->active_ios, io);

	ocs_unlock(&node->active_ios_lock);

	return io;
}