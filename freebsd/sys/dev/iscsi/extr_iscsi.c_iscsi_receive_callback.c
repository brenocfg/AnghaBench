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
struct iscsi_session {int /*<<< orphan*/  is_login_cv; struct icl_pdu* is_login_pdu; scalar_t__ is_login_phase; } ;
struct icl_pdu {TYPE_1__* ip_bhs; } ;
struct TYPE_2__ {int bhs_opcode; } ;

/* Variables and functions */
#define  ISCSI_BHS_OPCODE_ASYNC_MESSAGE 135 
#define  ISCSI_BHS_OPCODE_LOGOUT_RESPONSE 134 
#define  ISCSI_BHS_OPCODE_NOP_IN 133 
#define  ISCSI_BHS_OPCODE_R2T 132 
#define  ISCSI_BHS_OPCODE_REJECT 131 
#define  ISCSI_BHS_OPCODE_SCSI_DATA_IN 130 
#define  ISCSI_BHS_OPCODE_SCSI_RESPONSE 129 
#define  ISCSI_BHS_OPCODE_TASK_RESPONSE 128 
 int /*<<< orphan*/  ISCSI_SESSION_LOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_LOCK_ASSERT_NOT (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_UNLOCK (struct iscsi_session*) ; 
 int /*<<< orphan*/  ISCSI_SESSION_WARN (struct iscsi_session*,char*,int) ; 
 struct iscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_async_message (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_data_in (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_logout_response (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_nop_in (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_r2t (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_reject (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_scsi_response (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_handle_task_response (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_pdu_update_statsn (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_session_reconnect (struct iscsi_session*) ; 

__attribute__((used)) static void
iscsi_receive_callback(struct icl_pdu *response)
{
	struct iscsi_session *is;

	is = PDU_SESSION(response);

	ISCSI_SESSION_LOCK(is);

	iscsi_pdu_update_statsn(response);

#ifdef ICL_KERNEL_PROXY
	if (is->is_login_phase) {
		if (is->is_login_pdu == NULL)
			is->is_login_pdu = response;
		else
			icl_pdu_free(response);
		ISCSI_SESSION_UNLOCK(is);
		cv_signal(&is->is_login_cv);
		return;
	}
#endif

	/*
	 * The handling routine is responsible for freeing the PDU
	 * when it's no longer needed.
	 */
	switch (response->ip_bhs->bhs_opcode) {
	case ISCSI_BHS_OPCODE_NOP_IN:
		iscsi_pdu_handle_nop_in(response);
		ISCSI_SESSION_UNLOCK(is);
		break;
	case ISCSI_BHS_OPCODE_SCSI_RESPONSE:
		iscsi_pdu_handle_scsi_response(response);
		/* Session lock dropped inside. */
		ISCSI_SESSION_LOCK_ASSERT_NOT(is);
		break;
	case ISCSI_BHS_OPCODE_TASK_RESPONSE:
		iscsi_pdu_handle_task_response(response);
		ISCSI_SESSION_UNLOCK(is);
		break;
	case ISCSI_BHS_OPCODE_SCSI_DATA_IN:
		iscsi_pdu_handle_data_in(response);
		/* Session lock dropped inside. */
		ISCSI_SESSION_LOCK_ASSERT_NOT(is);
		break;
	case ISCSI_BHS_OPCODE_LOGOUT_RESPONSE:
		iscsi_pdu_handle_logout_response(response);
		ISCSI_SESSION_UNLOCK(is);
		break;
	case ISCSI_BHS_OPCODE_R2T:
		iscsi_pdu_handle_r2t(response);
		ISCSI_SESSION_UNLOCK(is);
		break;
	case ISCSI_BHS_OPCODE_ASYNC_MESSAGE:
		iscsi_pdu_handle_async_message(response);
		ISCSI_SESSION_UNLOCK(is);
		break;
	case ISCSI_BHS_OPCODE_REJECT:
		iscsi_pdu_handle_reject(response);
		ISCSI_SESSION_UNLOCK(is);
		break;
	default:
		ISCSI_SESSION_WARN(is, "received PDU with unsupported "
		    "opcode 0x%x; reconnecting",
		    response->ip_bhs->bhs_opcode);
		iscsi_session_reconnect(is);
		ISCSI_SESSION_UNLOCK(is);
		icl_pdu_free(response);
	}
}