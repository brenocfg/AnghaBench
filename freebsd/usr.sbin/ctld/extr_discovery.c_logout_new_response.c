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
struct pdu {scalar_t__ pdu_bhs; struct connection* pdu_connection; } ;
struct iscsi_bhs_logout_response {int bhslr_flags; void* bhslr_maxcmdsn; void* bhslr_expcmdsn; void* bhslr_statsn; int /*<<< orphan*/  bhslr_initiator_task_tag; int /*<<< orphan*/  bhslr_response; int /*<<< orphan*/  bhslr_opcode; } ;
struct iscsi_bhs_logout_request {int /*<<< orphan*/  bhslr_initiator_task_tag; } ;
struct connection {int /*<<< orphan*/  conn_cmdsn; int /*<<< orphan*/  conn_statsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSLR_RESPONSE_CLOSED_SUCCESSFULLY ; 
 int /*<<< orphan*/  ISCSI_BHS_OPCODE_LOGOUT_RESPONSE ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 struct pdu* pdu_new_response (struct pdu*) ; 

__attribute__((used)) static struct pdu *
logout_new_response(struct pdu *request)
{
	struct pdu *response;
	struct connection *conn;
	struct iscsi_bhs_logout_request *bhslr;
	struct iscsi_bhs_logout_response *bhslr2;

	bhslr = (struct iscsi_bhs_logout_request *)request->pdu_bhs;
	conn = request->pdu_connection;

	response = pdu_new_response(request);
	bhslr2 = (struct iscsi_bhs_logout_response *)response->pdu_bhs;
	bhslr2->bhslr_opcode = ISCSI_BHS_OPCODE_LOGOUT_RESPONSE;
	bhslr2->bhslr_flags = 0x80;
	bhslr2->bhslr_response = BHSLR_RESPONSE_CLOSED_SUCCESSFULLY;
	bhslr2->bhslr_initiator_task_tag = bhslr->bhslr_initiator_task_tag;
	bhslr2->bhslr_statsn = htonl(conn->conn_statsn++);
	bhslr2->bhslr_expcmdsn = htonl(conn->conn_cmdsn);
	bhslr2->bhslr_maxcmdsn = htonl(conn->conn_cmdsn);

	return (response);
}