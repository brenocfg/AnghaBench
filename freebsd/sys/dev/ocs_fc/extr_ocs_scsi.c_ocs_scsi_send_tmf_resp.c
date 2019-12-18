#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_16__ {int /*<<< orphan*/  timeout; int /*<<< orphan*/  cs_ctl; scalar_t__ offset; int /*<<< orphan*/  ox_id; } ;
struct TYPE_18__ {TYPE_3__ fcp_tgt; scalar_t__ fcp_rsp_len; scalar_t__ data; int /*<<< orphan*/  flags; } ;
struct TYPE_14__ {int /*<<< orphan*/  phys; TYPE_6__* virt; } ;
struct TYPE_17__ {int wire_len; scalar_t__ tmf_cmd; int sgl_count; int /*<<< orphan*/  timeout; TYPE_6__ iparam; int /*<<< orphan*/  cs_ctl; int /*<<< orphan*/  init_task_tag; TYPE_2__* sgl; TYPE_1__ rspbuf; void* scsi_tgt_cb_arg; int /*<<< orphan*/  scsi_tgt_cb; int /*<<< orphan*/  hio_type; int /*<<< orphan*/  hw_dif; struct TYPE_17__* ocs; struct TYPE_17__* node; } ;
typedef  TYPE_4__ ocs_t ;
typedef  int ocs_scsi_tmf_resp_e ;
typedef  int /*<<< orphan*/  ocs_scsi_io_cb_t ;
typedef  TYPE_4__ ocs_io_t ;
typedef  int int32_t ;
typedef  TYPE_6__ fcp_rsp_iu_t ;
struct TYPE_19__ {int /*<<< orphan*/  rsp_code; int /*<<< orphan*/  addl_rsp_info; } ;
typedef  TYPE_7__ fcp_rsp_info_t ;
struct TYPE_15__ {int len; scalar_t__ dif_addr; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FCP_RSP_LEN_VALID ; 
 int /*<<< orphan*/  FCP_TMF_COMPLETE ; 
 int /*<<< orphan*/  FCP_TMF_FAILED ; 
 int /*<<< orphan*/  FCP_TMF_INCORRECT_LUN ; 
 int /*<<< orphan*/  FCP_TMF_REJECTED ; 
 int /*<<< orphan*/  FCP_TMF_SUCCEEDED ; 
 int /*<<< orphan*/  OCS_HW_IO_TARGET_RSP ; 
 scalar_t__ OCS_SCSI_TMF_ABORT_TASK ; 
#define  OCS_SCSI_TMF_FUNCTION_COMPLETE 133 
#define  OCS_SCSI_TMF_FUNCTION_IO_NOT_FOUND 132 
#define  OCS_SCSI_TMF_FUNCTION_REJECTED 131 
#define  OCS_SCSI_TMF_FUNCTION_SUCCEEDED 130 
#define  OCS_SCSI_TMF_INCORRECT_LOGICAL_UNIT_NUMBER 129 
#define  OCS_SCSI_TMF_SERVICE_DELIVERY 128 
 int /*<<< orphan*/  ocs_assert (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ocs_htobe32 (int) ; 
 int /*<<< orphan*/  ocs_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ocs_memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ocs_scsi_convert_dif_info (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int ocs_scsi_io_dispatch (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocs_target_io_cb ; 
 int ocs_target_send_bls_resp (TYPE_4__*,int /*<<< orphan*/ ,void*) ; 

int32_t
ocs_scsi_send_tmf_resp(ocs_io_t *io, ocs_scsi_tmf_resp_e rspcode, uint8_t addl_rsp_info[3],
		ocs_scsi_io_cb_t cb, void *arg)
{
	int32_t rc = -1;
	ocs_t *ocs = NULL;
	fcp_rsp_iu_t *fcprsp = NULL;
	fcp_rsp_info_t *rspinfo = NULL;
	uint8_t fcp_rspcode;

	ocs_assert(io, -1);
	ocs_assert(io->ocs, -1);
	ocs_assert(io->node, -1);

	ocs = io->ocs;

	io->wire_len = 0;
	ocs_scsi_convert_dif_info(ocs, NULL, &io->hw_dif);

	switch(rspcode) {
	case OCS_SCSI_TMF_FUNCTION_COMPLETE:
		fcp_rspcode = FCP_TMF_COMPLETE;
		break;
	case OCS_SCSI_TMF_FUNCTION_SUCCEEDED:
	case OCS_SCSI_TMF_FUNCTION_IO_NOT_FOUND:
		fcp_rspcode = FCP_TMF_SUCCEEDED;
		break;
	case OCS_SCSI_TMF_FUNCTION_REJECTED:
		fcp_rspcode = FCP_TMF_REJECTED;
		break;
	case OCS_SCSI_TMF_INCORRECT_LOGICAL_UNIT_NUMBER:
		fcp_rspcode = FCP_TMF_INCORRECT_LUN;
		break;
	case OCS_SCSI_TMF_SERVICE_DELIVERY:
		fcp_rspcode = FCP_TMF_FAILED;
		break;
	default:
		fcp_rspcode = FCP_TMF_REJECTED;
		break;
	}

	io->hio_type = OCS_HW_IO_TARGET_RSP;

	io->scsi_tgt_cb = cb;
	io->scsi_tgt_cb_arg = arg;

	if (io->tmf_cmd == OCS_SCSI_TMF_ABORT_TASK) {
		rc = ocs_target_send_bls_resp(io, cb, arg);
		return rc;
	}

	/* populate the FCP TMF response */
	fcprsp = io->rspbuf.virt;
	ocs_memset(fcprsp, 0, sizeof(*fcprsp));

	fcprsp->flags |= FCP_RSP_LEN_VALID;

	rspinfo = (fcp_rsp_info_t*) fcprsp->data;
	if (addl_rsp_info != NULL) {
		ocs_memcpy(rspinfo->addl_rsp_info, addl_rsp_info, sizeof(rspinfo->addl_rsp_info));
	}
	rspinfo->rsp_code = fcp_rspcode;

	io->wire_len = sizeof(*fcprsp) - sizeof(fcprsp->data) + sizeof(*rspinfo);

	*((uint32_t*)fcprsp->fcp_rsp_len) = ocs_htobe32(sizeof(*rspinfo));

	io->sgl[0].addr = io->rspbuf.phys;
	io->sgl[0].dif_addr = 0;
	io->sgl[0].len = io->wire_len;
	io->sgl_count = 1;

	ocs_memset(&io->iparam, 0, sizeof(io->iparam));
	io->iparam.fcp_tgt.ox_id = io->init_task_tag;
	io->iparam.fcp_tgt.offset = 0;
	io->iparam.fcp_tgt.cs_ctl = io->cs_ctl;
	io->iparam.fcp_tgt.timeout = io->timeout;

	rc = ocs_scsi_io_dispatch(io, ocs_target_io_cb);

	return rc;
}