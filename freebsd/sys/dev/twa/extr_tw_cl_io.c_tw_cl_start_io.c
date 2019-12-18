#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tw_cli_req_context {int /*<<< orphan*/  request_id; TYPE_5__* cmd_pkt; int /*<<< orphan*/  flags; int /*<<< orphan*/  tw_cli_callback; struct tw_cl_req_packet* orig_req; struct tw_cl_req_handle* req_handle; } ;
struct tw_cli_ctlr_context {scalar_t__ working_srl; scalar_t__ reset_in_progress; int /*<<< orphan*/ * req_q_head; } ;
struct tw_cl_scsi_req_packet {int /*<<< orphan*/  sgl_entries; int /*<<< orphan*/  sg_list; scalar_t__ lun; int /*<<< orphan*/  cdb_len; int /*<<< orphan*/  cdb; scalar_t__ unit; } ;
struct TYPE_6__ {struct tw_cl_scsi_req_packet scsi_req; } ;
struct tw_cl_req_packet {int status; int flags; int /*<<< orphan*/  (* tw_osl_sgl_callback ) (struct tw_cl_req_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;TYPE_1__ gen_req_pkt; int /*<<< orphan*/  (* tw_osl_callback ) (struct tw_cl_req_handle*) ;} ;
struct tw_cl_req_handle {struct tw_cli_req_context* cl_req_ctxt; } ;
struct tw_cl_ctlr_handle {scalar_t__ cl_ctlr_ctxt; } ;
struct tw_cl_command_9k {int sgl_offset; int /*<<< orphan*/  sg_list; void* lun_h4__sgl_entries; int /*<<< orphan*/  cdb; scalar_t__ status; void* lun_l4__req_id; scalar_t__ unit; int /*<<< orphan*/  res__opcode; } ;
struct TYPE_8__ {int size_header; } ;
struct TYPE_9__ {TYPE_3__ header_desc; } ;
struct TYPE_7__ {struct tw_cl_command_9k cmd_pkt_9k; } ;
struct TYPE_10__ {TYPE_4__ cmd_hdr; TYPE_2__ command; } ;
typedef  scalar_t__ TW_UINT8 ;
typedef  int /*<<< orphan*/  TW_UINT32 ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_LUN_H4__SGL_ENTRIES (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_LUN_L4__REQ_ID (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUILD_RES__OPCODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWA_CONTROL_UNMASK_COMMAND_INTERRUPT ; 
 int /*<<< orphan*/  TWA_FW_CMD_EXECUTE_SCSI ; 
 scalar_t__ TWA_MULTI_LUN_FW_SRL ; 
 size_t TW_CLI_FREE_Q ; 
 size_t TW_CLI_PENDING_Q ; 
 int /*<<< orphan*/  TW_CLI_REQ_FLAGS_9K ; 
 int /*<<< orphan*/  TW_CLI_REQ_FLAGS_EXTERNAL ; 
 int /*<<< orphan*/  TW_CLI_WRITE_CONTROL_REGISTER (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 
 int TW_CL_ERR_REQ_INVALID_LUN ; 
 int TW_CL_ERR_REQ_SCSI_ERROR ; 
 int /*<<< orphan*/  TW_CL_ERR_REQ_SUCCESS ; 
 struct tw_cli_req_context* TW_CL_NULL ; 
 struct tw_cli_req_context* TW_CL_Q_FIRST_ITEM (int /*<<< orphan*/ *) ; 
 int TW_CL_REQ_CALLBACK_FOR_SGLIST ; 
 void* TW_CL_SWAP16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TW_OSL_EBUSY ; 
 int /*<<< orphan*/  stub1 (struct tw_cl_req_handle*) ; 
 int /*<<< orphan*/  stub2 (struct tw_cl_req_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_cli_complete_io ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  tw_cli_fill_sg_list (struct tw_cli_ctlr_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct tw_cli_req_context* tw_cli_get_request (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_cli_req_q_insert_tail (struct tw_cli_req_context*,size_t) ; 
 int /*<<< orphan*/  tw_cli_submit_cmd (struct tw_cli_req_context*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 int /*<<< orphan*/  tw_osl_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

TW_INT32
tw_cl_start_io(struct tw_cl_ctlr_handle *ctlr_handle,
	struct tw_cl_req_packet *req_pkt, struct tw_cl_req_handle *req_handle)
{
	struct tw_cli_ctlr_context		*ctlr;
	struct tw_cli_req_context		*req;
	struct tw_cl_command_9k			*cmd;
	struct tw_cl_scsi_req_packet		*scsi_req;
	TW_INT32				error = TW_CL_ERR_REQ_SUCCESS;

	tw_cli_dbg_printf(10, ctlr_handle, tw_osl_cur_func(), "entered");

	ctlr = (struct tw_cli_ctlr_context *)(ctlr_handle->cl_ctlr_ctxt);

	/*
	 * If working with a firmware version that does not support multiple
	 * luns, and this request is directed at a non-zero lun, error it
	 * back right away.
	 */
	if ((req_pkt->gen_req_pkt.scsi_req.lun) &&
		(ctlr->working_srl < TWA_MULTI_LUN_FW_SRL)) {
		req_pkt->status |= (TW_CL_ERR_REQ_INVALID_LUN |
			TW_CL_ERR_REQ_SCSI_ERROR);
		req_pkt->tw_osl_callback(req_handle);
		return(TW_CL_ERR_REQ_SUCCESS);
	}

	if ((req = tw_cli_get_request(ctlr
		)) == TW_CL_NULL) {
		tw_cli_dbg_printf(2, ctlr_handle, tw_osl_cur_func(),
			"Out of request context packets: returning busy");
		return(TW_OSL_EBUSY);
	}

	req_handle->cl_req_ctxt = req;
	req->req_handle = req_handle;
	req->orig_req = req_pkt;
	req->tw_cli_callback = tw_cli_complete_io;

	req->flags |= TW_CLI_REQ_FLAGS_EXTERNAL;
	req->flags |= TW_CLI_REQ_FLAGS_9K;

	scsi_req = &(req_pkt->gen_req_pkt.scsi_req);

	/* Build the cmd pkt. */
	cmd = &(req->cmd_pkt->command.cmd_pkt_9k);

	req->cmd_pkt->cmd_hdr.header_desc.size_header = 128;

	cmd->res__opcode = BUILD_RES__OPCODE(0, TWA_FW_CMD_EXECUTE_SCSI);
	cmd->unit = (TW_UINT8)(scsi_req->unit);
	cmd->lun_l4__req_id = TW_CL_SWAP16(
		BUILD_LUN_L4__REQ_ID(scsi_req->lun, req->request_id));
	cmd->status = 0;
	cmd->sgl_offset = 16; /* offset from end of hdr = max cdb len */
	tw_osl_memcpy(cmd->cdb, scsi_req->cdb, scsi_req->cdb_len);

	if (req_pkt->flags & TW_CL_REQ_CALLBACK_FOR_SGLIST) {
		TW_UINT32	num_sgl_entries;

		req_pkt->tw_osl_sgl_callback(req_handle, cmd->sg_list,
			&num_sgl_entries);
		cmd->lun_h4__sgl_entries =
			TW_CL_SWAP16(BUILD_LUN_H4__SGL_ENTRIES(scsi_req->lun,
				num_sgl_entries));
	} else {
		cmd->lun_h4__sgl_entries =
			TW_CL_SWAP16(BUILD_LUN_H4__SGL_ENTRIES(scsi_req->lun,
				scsi_req->sgl_entries));
		tw_cli_fill_sg_list(ctlr, scsi_req->sg_list,
			cmd->sg_list, scsi_req->sgl_entries);
	}

	if (((TW_CL_Q_FIRST_ITEM(&(ctlr->req_q_head[TW_CLI_PENDING_Q]))) != TW_CL_NULL) ||
		(ctlr->reset_in_progress)) {
		tw_cli_req_q_insert_tail(req, TW_CLI_PENDING_Q);
		TW_CLI_WRITE_CONTROL_REGISTER(ctlr_handle,
			TWA_CONTROL_UNMASK_COMMAND_INTERRUPT);
	} else if ((error = tw_cli_submit_cmd(req))) {
		tw_cli_dbg_printf(2, ctlr_handle, tw_osl_cur_func(),
			"Could not start request. request = %p, error = %d",
			req, error);
		tw_cli_req_q_insert_tail(req, TW_CLI_FREE_Q);
	}
	return(error);
}