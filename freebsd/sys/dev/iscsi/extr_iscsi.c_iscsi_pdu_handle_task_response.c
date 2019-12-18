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
struct iscsi_session {int dummy; } ;
struct iscsi_outstanding {scalar_t__ io_datasn; int /*<<< orphan*/ * io_ccb; } ;
struct iscsi_bhs_task_management_response {scalar_t__ bhstmr_initiator_task_tag; scalar_t__ bhstmr_response; } ;
struct icl_pdu {scalar_t__ ip_bhs; } ;

/* Variables and functions */
 scalar_t__ BHSTMR_RESPONSE_FUNCTION_COMPLETE ; 
 int /*<<< orphan*/  CAM_REQ_ABORTED ; 
 int /*<<< orphan*/  ISCSI_SESSION_WARN (struct iscsi_session*,char*,scalar_t__) ; 
 struct iscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 
 struct iscsi_outstanding* iscsi_outstanding_find (struct iscsi_session*,scalar_t__) ; 
 int /*<<< orphan*/  iscsi_outstanding_remove (struct iscsi_session*,struct iscsi_outstanding*) ; 
 int /*<<< orphan*/  iscsi_session_reconnect (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsi_session_terminate_task (struct iscsi_session*,struct iscsi_outstanding*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iscsi_pdu_handle_task_response(struct icl_pdu *response)
{
	struct iscsi_bhs_task_management_response *bhstmr;
	struct iscsi_outstanding *io, *aio;
	struct iscsi_session *is;

	is = PDU_SESSION(response);

	bhstmr = (struct iscsi_bhs_task_management_response *)response->ip_bhs;
	io = iscsi_outstanding_find(is, bhstmr->bhstmr_initiator_task_tag);
	if (io == NULL || io->io_ccb != NULL) {
		ISCSI_SESSION_WARN(is, "bad itt 0x%x",
		    bhstmr->bhstmr_initiator_task_tag);
		icl_pdu_free(response);
		iscsi_session_reconnect(is);
		return;
	}

	if (bhstmr->bhstmr_response != BHSTMR_RESPONSE_FUNCTION_COMPLETE) {
		ISCSI_SESSION_WARN(is, "task response 0x%x",
		    bhstmr->bhstmr_response);
	} else {
		aio = iscsi_outstanding_find(is, io->io_datasn);
		if (aio != NULL && aio->io_ccb != NULL)
			iscsi_session_terminate_task(is, aio, CAM_REQ_ABORTED);
	}

	iscsi_outstanding_remove(is, io);
	icl_pdu_free(response);
}