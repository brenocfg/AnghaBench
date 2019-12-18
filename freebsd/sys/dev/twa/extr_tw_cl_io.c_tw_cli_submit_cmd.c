#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tw_cli_req_context {int flags; scalar_t__ state; scalar_t__ cmd_pkt_phys; scalar_t__ orig_req; struct tw_cli_ctlr_context* ctlr; } ;
struct tw_cli_ctlr_context {scalar_t__ device_id; int flags; int /*<<< orphan*/  io_lock; struct tw_cl_ctlr_handle* ctlr_handle; } ;
struct tw_cl_req_packet {int flags; } ;
struct tw_cl_ctlr_handle {int dummy; } ;
struct tw_cl_command_header {int dummy; } ;
typedef  int TW_UINT64 ;
typedef  int TW_UINT32 ;
typedef  int /*<<< orphan*/  TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TWA_COMMAND_QUEUE_OFFSET ; 
 int /*<<< orphan*/  TWA_COMMAND_QUEUE_OFFSET_HIGH ; 
 int /*<<< orphan*/  TWA_COMMAND_QUEUE_OFFSET_LOW ; 
 int /*<<< orphan*/  TWA_CONTROL_UNMASK_COMMAND_INTERRUPT ; 
 int TWA_STATUS_COMMAND_QUEUE_FULL ; 
 int /*<<< orphan*/  TW_CLI_BUSY_Q ; 
 int /*<<< orphan*/  TW_CLI_PENDING_Q ; 
 int TW_CLI_READ_STATUS_REGISTER (struct tw_cl_ctlr_handle*) ; 
 int TW_CLI_REQ_FLAGS_INTERNAL ; 
 scalar_t__ TW_CLI_REQ_STATE_BUSY ; 
 scalar_t__ TW_CLI_REQ_STATE_PENDING ; 
 int /*<<< orphan*/  TW_CLI_WRITE_CONTROL_REGISTER (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 
 int TW_CL_64BIT_ADDRESSES ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_E ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_SA ; 
 int TW_CL_REQ_RETRY_ON_BUSY ; 
 int /*<<< orphan*/  TW_OSL_EBUSY ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cli_req_q_insert_tail (struct tw_cli_req_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 int /*<<< orphan*/  tw_osl_free_lock (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_get_lock (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_write_reg (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,int,int) ; 

TW_INT32
tw_cli_submit_cmd(struct tw_cli_req_context *req)
{
	struct tw_cli_ctlr_context	*ctlr = req->ctlr;
	struct tw_cl_ctlr_handle	*ctlr_handle = ctlr->ctlr_handle;
	TW_UINT32			status_reg;
	TW_INT32			error = 0;

	tw_cli_dbg_printf(10, ctlr_handle, tw_osl_cur_func(), "entered");

	/* Serialize access to the controller cmd queue. */
	tw_osl_get_lock(ctlr_handle, ctlr->io_lock);

	/* For 9650SE first write low 4 bytes */
	if ((ctlr->device_id == TW_CL_DEVICE_ID_9K_E) ||
	    (ctlr->device_id == TW_CL_DEVICE_ID_9K_SA))
		tw_osl_write_reg(ctlr_handle,
				 TWA_COMMAND_QUEUE_OFFSET_LOW,
				 (TW_UINT32)(req->cmd_pkt_phys + sizeof(struct tw_cl_command_header)), 4);

	status_reg = TW_CLI_READ_STATUS_REGISTER(ctlr_handle);
	if (status_reg & TWA_STATUS_COMMAND_QUEUE_FULL) {
		struct tw_cl_req_packet	*req_pkt =
			(struct tw_cl_req_packet *)(req->orig_req);

		tw_cli_dbg_printf(7, ctlr_handle, tw_osl_cur_func(),
			"Cmd queue full");

		if ((req->flags & TW_CLI_REQ_FLAGS_INTERNAL)
			|| ((req_pkt) &&
			(req_pkt->flags & TW_CL_REQ_RETRY_ON_BUSY))
			) {
			if (req->state != TW_CLI_REQ_STATE_PENDING) {
				tw_cli_dbg_printf(2, ctlr_handle,
					tw_osl_cur_func(),
					"pending internal/ioctl request");
				req->state = TW_CLI_REQ_STATE_PENDING;
				tw_cli_req_q_insert_tail(req, TW_CLI_PENDING_Q);
				/* Unmask command interrupt. */
				TW_CLI_WRITE_CONTROL_REGISTER(ctlr_handle,
					TWA_CONTROL_UNMASK_COMMAND_INTERRUPT);
			} else
				error = TW_OSL_EBUSY;
		} else {
			error = TW_OSL_EBUSY;
		}
	} else {
		tw_cli_dbg_printf(10, ctlr_handle, tw_osl_cur_func(),
			"Submitting command");

		/* Insert command into busy queue */
		req->state = TW_CLI_REQ_STATE_BUSY;
		tw_cli_req_q_insert_tail(req, TW_CLI_BUSY_Q);

		if ((ctlr->device_id == TW_CL_DEVICE_ID_9K_E) ||
		    (ctlr->device_id == TW_CL_DEVICE_ID_9K_SA)) {
			/* Now write the high 4 bytes */
			tw_osl_write_reg(ctlr_handle, 
					 TWA_COMMAND_QUEUE_OFFSET_HIGH,
					 (TW_UINT32)(((TW_UINT64)(req->cmd_pkt_phys + sizeof(struct tw_cl_command_header)))>>32), 4);
		} else {
			if (ctlr->flags & TW_CL_64BIT_ADDRESSES) {
				/* First write the low 4 bytes, then the high 4. */
				tw_osl_write_reg(ctlr_handle,
						 TWA_COMMAND_QUEUE_OFFSET_LOW,
						 (TW_UINT32)(req->cmd_pkt_phys + sizeof(struct tw_cl_command_header)), 4);
				tw_osl_write_reg(ctlr_handle, 
						 TWA_COMMAND_QUEUE_OFFSET_HIGH,
						 (TW_UINT32)(((TW_UINT64)(req->cmd_pkt_phys + sizeof(struct tw_cl_command_header)))>>32), 4);
			} else
				tw_osl_write_reg(ctlr_handle, 
						 TWA_COMMAND_QUEUE_OFFSET,
						 (TW_UINT32)(req->cmd_pkt_phys + sizeof(struct tw_cl_command_header)), 4);
		}
	}

	tw_osl_free_lock(ctlr_handle, ctlr->io_lock);

	return(error);
}