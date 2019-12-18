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
struct tw_cli_req_context {int request_id; struct tw_cli_ctlr_context* ctlr; scalar_t__ cmd_pkt_phys; struct tw_cl_command_packet* cmd_pkt; } ;
struct tw_cli_ctlr_context {int device_id; int flags; int max_simult_reqs; int max_aens_supported; int /*<<< orphan*/  active; struct tw_cl_event_packet* aen_queue; scalar_t__ cmd_pkt_phys; struct tw_cl_command_packet* cmd_pkt_buf; struct tw_cli_req_context* req_ctxt_buf; scalar_t__ internal_req_data_phys; int /*<<< orphan*/ * internal_req_data; int /*<<< orphan*/ * io_lock; int /*<<< orphan*/  io_lock_handle; int /*<<< orphan*/ * gen_lock; int /*<<< orphan*/  gen_lock_handle; int /*<<< orphan*/  sg_size_factor; int /*<<< orphan*/  arch_id; struct tw_cl_ctlr_handle* ctlr_handle; } ;
struct tw_cl_event_packet {int dummy; } ;
struct tw_cl_ctlr_handle {struct tw_cli_ctlr_context* cl_ctlr_ctxt; } ;
struct tw_cl_command_packet {int dummy; } ;
typedef  int /*<<< orphan*/  TW_VOID ;
typedef  int /*<<< orphan*/  TW_UINT8 ;
typedef  scalar_t__ TW_UINT64 ;
typedef  int TW_UINT32 ;
typedef  int TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TWA_ARCH_ID (int) ; 
 int /*<<< orphan*/  TWA_SG_ELEMENT_SIZE_FACTOR (int) ; 
 int /*<<< orphan*/  TW_CLI_BUSY_Q ; 
 int /*<<< orphan*/  TW_CLI_COMPLETE_Q ; 
 int /*<<< orphan*/  TW_CLI_FREE_Q ; 
 int /*<<< orphan*/  TW_CLI_PENDING_Q ; 
 int /*<<< orphan*/  TW_CLI_RESET_Q ; 
 int TW_CLI_SECTOR_SIZE ; 
 int /*<<< orphan*/  TW_CL_FALSE ; 
 int TW_CL_MAX_SIMULTANEOUS_REQUESTS ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR ; 
 int /*<<< orphan*/ * TW_CL_NULL ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int TW_CL_START_CTLR_ONLY ; 
 int /*<<< orphan*/  TW_CL_TRUE ; 
 int TW_OSL_EBIG ; 
 int TW_OSL_ENOMEM ; 
 int TW_OSL_ESUCCESS ; 
 int /*<<< orphan*/  tw_cl_create_event (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tw_cli_disable_interrupts (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_cli_notify_ctlr_info (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_cli_req_q_init (struct tw_cli_ctlr_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_cli_req_q_insert_tail (struct tw_cli_req_context*,int /*<<< orphan*/ ) ; 
 int tw_cli_soft_reset (struct tw_cli_ctlr_context*) ; 
 int tw_cli_start_ctlr (struct tw_cli_ctlr_context*) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 int /*<<< orphan*/  tw_osl_init_lock (struct tw_cl_ctlr_handle*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tw_osl_memzero (int /*<<< orphan*/ *,int) ; 

TW_INT32
tw_cl_init_ctlr(struct tw_cl_ctlr_handle *ctlr_handle, TW_UINT32 flags,
	TW_INT32 device_id, TW_INT32 max_simult_reqs, TW_INT32 max_aens,
	TW_VOID *non_dma_mem, TW_VOID *dma_mem, TW_UINT64 dma_mem_phys
	)
{
	struct tw_cli_ctlr_context	*ctlr;
	struct tw_cli_req_context	*req;
	TW_UINT8			*free_non_dma_mem;
	TW_INT32			error = TW_OSL_ESUCCESS;
	TW_INT32			i;

	tw_cli_dbg_printf(3, ctlr_handle, tw_osl_cur_func(), "entered");

	if (flags & TW_CL_START_CTLR_ONLY) {
		ctlr = (struct tw_cli_ctlr_context *)
			(ctlr_handle->cl_ctlr_ctxt);
		goto start_ctlr;
	}

	if (max_simult_reqs > TW_CL_MAX_SIMULTANEOUS_REQUESTS) {
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
			0x1000, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Too many simultaneous requests to support!",
			"requested = %d, supported = %d, error = %d\n",
			max_simult_reqs, TW_CL_MAX_SIMULTANEOUS_REQUESTS,
			TW_OSL_EBIG);
		return(TW_OSL_EBIG);
	}

	if ((non_dma_mem == TW_CL_NULL) || (dma_mem == TW_CL_NULL)
		) {
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
			0x1001, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Insufficient memory for Common Layer's internal usage",
			"error = %d\n", TW_OSL_ENOMEM);
		return(TW_OSL_ENOMEM);
	}

	tw_osl_memzero(non_dma_mem, sizeof(struct tw_cli_ctlr_context) +
		(sizeof(struct tw_cli_req_context) * max_simult_reqs) +
		(sizeof(struct tw_cl_event_packet) * max_aens));

	tw_osl_memzero(dma_mem,
		(sizeof(struct tw_cl_command_packet) *
		max_simult_reqs) +
		TW_CLI_SECTOR_SIZE);

	free_non_dma_mem = (TW_UINT8 *)non_dma_mem;

	ctlr = (struct tw_cli_ctlr_context *)free_non_dma_mem;
	free_non_dma_mem += sizeof(struct tw_cli_ctlr_context);

	ctlr_handle->cl_ctlr_ctxt = ctlr;
	ctlr->ctlr_handle = ctlr_handle;

	ctlr->device_id = (TW_UINT32)device_id;
	ctlr->arch_id = TWA_ARCH_ID(device_id);
	ctlr->flags = flags;
	ctlr->sg_size_factor = TWA_SG_ELEMENT_SIZE_FACTOR(device_id);
	ctlr->max_simult_reqs = max_simult_reqs;
	ctlr->max_aens_supported = max_aens;

	/* Initialize queues of CL internal request context packets. */
	tw_cli_req_q_init(ctlr, TW_CLI_FREE_Q);
	tw_cli_req_q_init(ctlr, TW_CLI_BUSY_Q);
	tw_cli_req_q_init(ctlr, TW_CLI_PENDING_Q);
	tw_cli_req_q_init(ctlr, TW_CLI_COMPLETE_Q);
	tw_cli_req_q_init(ctlr, TW_CLI_RESET_Q);

	/* Initialize all locks used by CL. */
	ctlr->gen_lock = &(ctlr->gen_lock_handle);
	tw_osl_init_lock(ctlr_handle, "tw_cl_gen_lock", ctlr->gen_lock);
	ctlr->io_lock = &(ctlr->io_lock_handle);
	tw_osl_init_lock(ctlr_handle, "tw_cl_io_lock", ctlr->io_lock);

	/* Initialize CL internal request context packets. */
	ctlr->req_ctxt_buf = (struct tw_cli_req_context *)free_non_dma_mem;
	free_non_dma_mem += (sizeof(struct tw_cli_req_context) *
		max_simult_reqs);

	ctlr->cmd_pkt_buf = (struct tw_cl_command_packet *)dma_mem;
	ctlr->cmd_pkt_phys = dma_mem_phys;

	ctlr->internal_req_data = (TW_UINT8 *)
		(ctlr->cmd_pkt_buf +
		max_simult_reqs);
	ctlr->internal_req_data_phys = ctlr->cmd_pkt_phys +
		(sizeof(struct tw_cl_command_packet) *
		max_simult_reqs);

	for (i = 0; i < max_simult_reqs; i++) {
		req = &(ctlr->req_ctxt_buf[i]);

		req->cmd_pkt = &(ctlr->cmd_pkt_buf[i]);
		req->cmd_pkt_phys = ctlr->cmd_pkt_phys +
			(i * sizeof(struct tw_cl_command_packet));

		req->request_id = i;
		req->ctlr = ctlr;

		/* Insert request into the free queue. */
		tw_cli_req_q_insert_tail(req, TW_CLI_FREE_Q);
	}

	/* Initialize the AEN queue. */
	ctlr->aen_queue = (struct tw_cl_event_packet *)free_non_dma_mem;


start_ctlr:
	/*
	 * Disable interrupts.  Interrupts will be enabled in tw_cli_start_ctlr
	 * (only) if initialization succeeded.
	 */
	tw_cli_disable_interrupts(ctlr);

	/* Initialize the controller. */
	if ((error = tw_cli_start_ctlr(ctlr))) {
		/* Soft reset the controller, and try one more time. */
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
			0x1002, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Controller initialization failed. Retrying...",
			"error = %d\n", error);
		if ((error = tw_cli_soft_reset(ctlr))) {
			tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
				TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
				0x1003, 0x1, TW_CL_SEVERITY_ERROR_STRING,
				"Controller soft reset failed",
				"error = %d\n", error);
			return(error);
		} else if ((error = tw_cli_start_ctlr(ctlr))) {
			tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
				TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
				0x1004, 0x1, TW_CL_SEVERITY_ERROR_STRING,
				"Controller initialization retry failed",
				"error = %d\n", error);
			return(error);
		}
	}
	/* Notify some info about the controller to the OSL. */
	tw_cli_notify_ctlr_info(ctlr);

	/* Mark the controller active. */
	ctlr->active = TW_CL_TRUE;
	return(error);
}