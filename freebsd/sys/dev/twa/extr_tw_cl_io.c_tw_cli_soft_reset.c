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
struct tw_cli_ctlr_context {scalar_t__ device_id; int /*<<< orphan*/  io_lock; int /*<<< orphan*/  reset_phase1_in_progress; struct tw_cl_ctlr_handle* ctlr_handle; } ;
struct tw_cl_ctlr_handle {int dummy; } ;
typedef  int TW_UINT32 ;
typedef  int TW_INT32 ;

/* Variables and functions */
 int /*<<< orphan*/  TWA_AEN_SOFT_RESET ; 
 int /*<<< orphan*/  TWA_CONTROL_CLEAR_ATTENTION_INTERRUPT ; 
 int /*<<< orphan*/  TWA_RESET_PHASE1_NOTIFICATION_RESPONSE ; 
 int TWA_RESET_PHASE1_WAIT_TIME_MS ; 
 int TWA_STATUS_ATTENTION_INTERRUPT ; 
 int TWA_STATUS_MICROCONTROLLER_READY ; 
 int /*<<< orphan*/  TW_CLI_RESET_TIMEOUT_PERIOD ; 
 int /*<<< orphan*/  TW_CLI_SOFT_RESET (struct tw_cl_ctlr_handle*) ; 
 int /*<<< orphan*/  TW_CLI_WRITE_CONTROL_REGISTER (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_E ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_SA ; 
 scalar_t__ TW_CL_DEVICE_ID_9K_X ; 
 int /*<<< orphan*/  TW_CL_FALSE ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR ; 
 int /*<<< orphan*/  TW_CL_MESSAGE_SOURCE_COMMON_LAYER_EVENT ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_ERROR_STRING ; 
 int /*<<< orphan*/  TW_CL_SEVERITY_INFO_STRING ; 
 int /*<<< orphan*/  TW_CL_TRUE ; 
 scalar_t__ TW_OSL_ESUCCESS ; 
 int /*<<< orphan*/  tw_cl_create_event (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  tw_cli_dbg_printf (int,struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ,char*) ; 
 int tw_cli_drain_aen_queue (struct tw_cli_ctlr_context*) ; 
 int tw_cli_drain_response_queue (struct tw_cli_ctlr_context*) ; 
 int tw_cli_find_aen (struct tw_cli_ctlr_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ tw_cli_find_response (struct tw_cli_ctlr_context*,int /*<<< orphan*/ ) ; 
 int tw_cli_poll_status (struct tw_cli_ctlr_context*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_cur_func () ; 
 int /*<<< orphan*/  tw_osl_delay (int) ; 
 int /*<<< orphan*/  tw_osl_free_lock (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw_osl_get_lock (struct tw_cl_ctlr_handle*,int /*<<< orphan*/ ) ; 

TW_INT32
tw_cli_soft_reset(struct tw_cli_ctlr_context *ctlr)
{
	struct tw_cl_ctlr_handle	*ctlr_handle = ctlr->ctlr_handle;
	int				found;
	int				loop_count;
	TW_UINT32			error;

	tw_cli_dbg_printf(1, ctlr_handle, tw_osl_cur_func(), "entered");

	tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
		TW_CL_MESSAGE_SOURCE_COMMON_LAYER_EVENT,
		0x1108, 0x3, TW_CL_SEVERITY_INFO_STRING,
		"Resetting controller...",
		" ");

	/* Don't let any new commands get submitted to the controller. */
	tw_osl_get_lock(ctlr_handle, ctlr->io_lock);

	TW_CLI_SOFT_RESET(ctlr_handle);

	if ((ctlr->device_id == TW_CL_DEVICE_ID_9K_X) ||
	    (ctlr->device_id == TW_CL_DEVICE_ID_9K_E) ||
	    (ctlr->device_id == TW_CL_DEVICE_ID_9K_SA)) {
		/*
		 * There's a hardware bug in the G133 ASIC, which can lead to
		 * PCI parity errors and hangs, if the host accesses any
		 * registers when the firmware is resetting the hardware, as
		 * part of a hard/soft reset.  The window of time when the
		 * problem can occur is about 10 ms.  Here, we will handshake
		 * with the firmware to find out when the firmware is pulling
		 * down the hardware reset pin, and wait for about 500 ms to
		 * make sure we don't access any hardware registers (for
		 * polling) during that window.
		 */
		ctlr->reset_phase1_in_progress = TW_CL_TRUE;
		loop_count = 0;
		do {
			found = (tw_cli_find_response(ctlr, TWA_RESET_PHASE1_NOTIFICATION_RESPONSE) == TW_OSL_ESUCCESS);
			tw_osl_delay(10);
			loop_count++;
			error = 0x7888;
		} while (!found && (loop_count < 6000000)); /* Loop for no more than 60 seconds */

		if (!found) {
			tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
				TW_CL_MESSAGE_SOURCE_COMMON_LAYER_EVENT,
				0x1109, 0x1, TW_CL_SEVERITY_ERROR_STRING,
				"Missed firmware handshake after soft-reset",
				"error = %d", error);
			tw_osl_free_lock(ctlr_handle, ctlr->io_lock);
			return(error);
		}

		tw_osl_delay(TWA_RESET_PHASE1_WAIT_TIME_MS * 1000);
		ctlr->reset_phase1_in_progress = TW_CL_FALSE;
	}

	if ((error = tw_cli_poll_status(ctlr,
			TWA_STATUS_MICROCONTROLLER_READY |
			TWA_STATUS_ATTENTION_INTERRUPT,
			TW_CLI_RESET_TIMEOUT_PERIOD))) {
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_EVENT,
			0x1109, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Micro-ctlr not ready/No attn intr after reset",
			"error = %d", error);
		tw_osl_free_lock(ctlr_handle, ctlr->io_lock);
		return(error);
	}

	TW_CLI_WRITE_CONTROL_REGISTER(ctlr_handle,
		TWA_CONTROL_CLEAR_ATTENTION_INTERRUPT);

	if ((error = tw_cli_drain_response_queue(ctlr))) {
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
			0x110A, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Can't drain response queue after reset",
			"error = %d", error);
		tw_osl_free_lock(ctlr_handle, ctlr->io_lock);
		return(error);
	}
	
	tw_osl_free_lock(ctlr_handle, ctlr->io_lock);

	if ((error = tw_cli_drain_aen_queue(ctlr))) {
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_ERROR,
			0x110B, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Can't drain AEN queue after reset",
			"error = %d", error);
		return(error);
	}
	
	if ((error = tw_cli_find_aen(ctlr, TWA_AEN_SOFT_RESET))) {
		tw_cl_create_event(ctlr_handle, TW_CL_FALSE,
			TW_CL_MESSAGE_SOURCE_COMMON_LAYER_EVENT,
			0x110C, 0x1, TW_CL_SEVERITY_ERROR_STRING,
			"Reset not reported by controller",
			"error = %d", error);
		return(error);
	}

	return(TW_OSL_ESUCCESS);
}