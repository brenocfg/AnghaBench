#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ocs_scsi_io_cb_t ;
struct TYPE_8__ {int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; TYPE_6__* payload; } ;
struct TYPE_11__ {TYPE_1__ bls; } ;
struct TYPE_9__ {char* display_name; void* bls_cb_arg; int /*<<< orphan*/  bls_cb; int /*<<< orphan*/  hio_type; int /*<<< orphan*/  io_type; TYPE_6__ iparam; int /*<<< orphan*/  abort_rx_id; int /*<<< orphan*/  init_task_tag; } ;
typedef  TYPE_2__ ocs_io_t ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_10__ {int /*<<< orphan*/  high_seq_cnt; int /*<<< orphan*/  rx_id; int /*<<< orphan*/  ox_id; } ;
typedef  TYPE_3__ fc_ba_acc_payload_t ;

/* Variables and functions */
 int /*<<< orphan*/  OCS_HW_BLS_ACC ; 
 int /*<<< orphan*/  OCS_IO_TYPE_BLS_RESP ; 
 int /*<<< orphan*/  UINT16_MAX ; 
 int /*<<< orphan*/  ocs_assert (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_scsi_io_dispatch (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_target_bls_resp_cb ; 

__attribute__((used)) static int32_t
ocs_target_send_bls_resp(ocs_io_t *io, ocs_scsi_io_cb_t cb, void *arg)
{
	int32_t rc;
	fc_ba_acc_payload_t *acc;

	ocs_assert(io, -1);

	/* fill out IO structure with everything needed to send BA_ACC */
	ocs_memset(&io->iparam, 0, sizeof(io->iparam));
	io->iparam.bls.ox_id = io->init_task_tag;
	io->iparam.bls.rx_id = io->abort_rx_id;

	acc = (void *)io->iparam.bls.payload;

	ocs_memset(io->iparam.bls.payload, 0, sizeof(io->iparam.bls.payload));
	acc->ox_id = io->iparam.bls.ox_id;
	acc->rx_id = io->iparam.bls.rx_id;
	acc->high_seq_cnt = UINT16_MAX;

	/* generic io fields have already been populated */

	/* set type and BLS-specific fields */
	io->io_type = OCS_IO_TYPE_BLS_RESP;
	io->display_name = "bls_rsp";
	io->hio_type = OCS_HW_BLS_ACC;
	io->bls_cb = cb;
	io->bls_cb_arg = arg;

	/* dispatch IO */
	rc = ocs_scsi_io_dispatch(io, ocs_target_bls_resp_cb);
	return rc;
}