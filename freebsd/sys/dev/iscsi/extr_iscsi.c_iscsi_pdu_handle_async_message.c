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
struct iscsi_bhs_asynchronous_message {int bhsam_async_event; } ;
struct icl_pdu {scalar_t__ ip_bhs; } ;

/* Variables and functions */
#define  BHSAM_EVENT_TARGET_REQUESTS_LOGOUT 130 
#define  BHSAM_EVENT_TARGET_TERMINATES_CONNECTION 129 
#define  BHSAM_EVENT_TARGET_TERMINATES_SESSION 128 
 int /*<<< orphan*/  ISCSI_SESSION_WARN (struct iscsi_session*,char*,...) ; 
 struct iscsi_session* PDU_SESSION (struct icl_pdu*) ; 
 int /*<<< orphan*/  icl_pdu_free (struct icl_pdu*) ; 
 int /*<<< orphan*/  iscsi_session_logout (struct iscsi_session*) ; 
 int /*<<< orphan*/  iscsi_session_terminate (struct iscsi_session*) ; 

__attribute__((used)) static void
iscsi_pdu_handle_async_message(struct icl_pdu *response)
{
	struct iscsi_bhs_asynchronous_message *bhsam;
	struct iscsi_session *is;

	is = PDU_SESSION(response);
	bhsam = (struct iscsi_bhs_asynchronous_message *)response->ip_bhs;
	switch (bhsam->bhsam_async_event) {
	case BHSAM_EVENT_TARGET_REQUESTS_LOGOUT:
		ISCSI_SESSION_WARN(is, "target requests logout; removing session");
		iscsi_session_logout(is);
		iscsi_session_terminate(is);
		break;
	case BHSAM_EVENT_TARGET_TERMINATES_CONNECTION:
		ISCSI_SESSION_WARN(is, "target indicates it will drop the connection");
		break;
	case BHSAM_EVENT_TARGET_TERMINATES_SESSION:
		ISCSI_SESSION_WARN(is, "target indicates it will drop the session");
		break;
	default:
		/*
		 * XXX: Technically, we're obligated to also handle
		 * 	parameter renegotiation.
		 */
		ISCSI_SESSION_WARN(is, "ignoring AsyncEvent %d", bhsam->bhsam_async_event);
		break;
	}

	icl_pdu_free(response);
}