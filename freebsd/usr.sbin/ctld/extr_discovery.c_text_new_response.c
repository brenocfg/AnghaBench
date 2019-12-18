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
struct iscsi_bhs_text_response {void* bhstr_maxcmdsn; void* bhstr_expcmdsn; void* bhstr_statsn; int /*<<< orphan*/  bhstr_target_transfer_tag; int /*<<< orphan*/  bhstr_initiator_task_tag; int /*<<< orphan*/  bhstr_lun; int /*<<< orphan*/  bhstr_flags; int /*<<< orphan*/  bhstr_opcode; } ;
struct iscsi_bhs_text_request {int /*<<< orphan*/  bhstr_target_transfer_tag; int /*<<< orphan*/  bhstr_initiator_task_tag; int /*<<< orphan*/  bhstr_lun; } ;
struct connection {int /*<<< orphan*/  conn_cmdsn; int /*<<< orphan*/  conn_statsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSTR_FLAGS_FINAL ; 
 int /*<<< orphan*/  ISCSI_BHS_OPCODE_TEXT_RESPONSE ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 struct pdu* pdu_new_response (struct pdu*) ; 

__attribute__((used)) static struct pdu *
text_new_response(struct pdu *request)
{
	struct pdu *response;
	struct connection *conn;
	struct iscsi_bhs_text_request *bhstr;
	struct iscsi_bhs_text_response *bhstr2;

	bhstr = (struct iscsi_bhs_text_request *)request->pdu_bhs;
	conn = request->pdu_connection;

	response = pdu_new_response(request);
	bhstr2 = (struct iscsi_bhs_text_response *)response->pdu_bhs;
	bhstr2->bhstr_opcode = ISCSI_BHS_OPCODE_TEXT_RESPONSE;
	bhstr2->bhstr_flags = BHSTR_FLAGS_FINAL;
	bhstr2->bhstr_lun = bhstr->bhstr_lun;
	bhstr2->bhstr_initiator_task_tag = bhstr->bhstr_initiator_task_tag;
	bhstr2->bhstr_target_transfer_tag = bhstr->bhstr_target_transfer_tag;
	bhstr2->bhstr_statsn = htonl(conn->conn_statsn++);
	bhstr2->bhstr_expcmdsn = htonl(conn->conn_cmdsn);
	bhstr2->bhstr_maxcmdsn = htonl(conn->conn_cmdsn);

	return (response);
}