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
struct iscsi_session {int /*<<< orphan*/  is_conn; } ;
struct iscsi_bhs_logout_request {int /*<<< orphan*/  bhslr_reason; int /*<<< orphan*/  bhslr_opcode; } ;
struct icl_pdu {scalar_t__ ip_bhs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSLR_REASON_CLOSE_SESSION ; 
 int /*<<< orphan*/  ISCSI_BHS_OPCODE_LOGOUT_REQUEST ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 struct icl_pdu* icl_pdu_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_pdu_queue_locked (struct icl_pdu*) ; 

__attribute__((used)) static void
iscsi_session_logout(struct iscsi_session *is)
{
	struct icl_pdu *request;
	struct iscsi_bhs_logout_request *bhslr;

	request = icl_pdu_new(is->is_conn, M_NOWAIT);
	if (request == NULL)
		return;

	bhslr = (struct iscsi_bhs_logout_request *)request->ip_bhs;
	bhslr->bhslr_opcode = ISCSI_BHS_OPCODE_LOGOUT_REQUEST;
	bhslr->bhslr_reason = BHSLR_REASON_CLOSE_SESSION;
	iscsi_pdu_queue_locked(request);
}