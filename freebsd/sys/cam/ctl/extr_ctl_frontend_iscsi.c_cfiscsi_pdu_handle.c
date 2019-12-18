#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct icl_pdu {TYPE_1__* ip_bhs; } ;
struct cfiscsi_session {int dummy; } ;
struct TYPE_2__ {int bhs_opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFISCSI_SESSION_WARN (struct cfiscsi_session*,char*,int) ; 
 int ISCSI_BHS_OPCODE_IMMEDIATE ; 
#define  ISCSI_BHS_OPCODE_LOGOUT_REQUEST 132 
#define  ISCSI_BHS_OPCODE_NOP_OUT 131 
#define  ISCSI_BHS_OPCODE_SCSI_COMMAND 130 
#define  ISCSI_BHS_OPCODE_SCSI_DATA_OUT 129 
#define  ISCSI_BHS_OPCODE_TASK_REQUEST 128 
 struct cfiscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_pdu_handle_data_out (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_pdu_handle_logout_request (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_pdu_handle_nop_out (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_pdu_handle_scsi_command (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_pdu_handle_task_request (struct icl_pdu*) ; 
 int cfiscsi_pdu_update_cmdsn (struct icl_pdu*) ; 
 int /*<<< orphan*/  cfiscsi_session_terminate (struct cfiscsi_session*) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 

__attribute__((used)) static void
cfiscsi_pdu_handle(struct icl_pdu *request)
{
	struct cfiscsi_session *cs;
	bool ignore;

	cs = PDU_SESSION(request);

	ignore = cfiscsi_pdu_update_cmdsn(request);
	if (ignore) {
		icl_pdu_free(request);
		return;
	}

	/*
	 * Handle the PDU; this includes e.g. receiving the remaining
	 * part of PDU and submitting the SCSI command to CTL
	 * or queueing a reply.  The handling routine is responsible
	 * for freeing the PDU when it's no longer needed.
	 */
	switch (request->ip_bhs->bhs_opcode &
	    ~ISCSI_BHS_OPCODE_IMMEDIATE) {
	case ISCSI_BHS_OPCODE_NOP_OUT:
		cfiscsi_pdu_handle_nop_out(request);
		break;
	case ISCSI_BHS_OPCODE_SCSI_COMMAND:
		cfiscsi_pdu_handle_scsi_command(request);
		break;
	case ISCSI_BHS_OPCODE_TASK_REQUEST:
		cfiscsi_pdu_handle_task_request(request);
		break;
	case ISCSI_BHS_OPCODE_SCSI_DATA_OUT:
		cfiscsi_pdu_handle_data_out(request);
		break;
	case ISCSI_BHS_OPCODE_LOGOUT_REQUEST:
		cfiscsi_pdu_handle_logout_request(request);
		break;
	default:
		CFISCSI_SESSION_WARN(cs, "received PDU with unsupported "
		    "opcode 0x%x; dropping connection",
		    request->ip_bhs->bhs_opcode);
		icl_pdu_free(request);
		cfiscsi_session_terminate(cs);
	}

}