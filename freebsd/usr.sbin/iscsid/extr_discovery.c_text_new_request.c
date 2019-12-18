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
struct pdu {scalar_t__ pdu_bhs; } ;
struct iscsi_bhs_text_request {int bhstr_opcode; int bhstr_target_transfer_tag; int /*<<< orphan*/  bhstr_expstatsn; scalar_t__ bhstr_cmdsn; scalar_t__ bhstr_initiator_task_tag; int /*<<< orphan*/  bhstr_flags; } ;
struct connection {scalar_t__ conn_statsn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSTR_FLAGS_FINAL ; 
 int ISCSI_BHS_OPCODE_IMMEDIATE ; 
 int ISCSI_BHS_OPCODE_TEXT_REQUEST ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 struct pdu* pdu_new (struct connection*) ; 

__attribute__((used)) static struct pdu *
text_new_request(struct connection *conn)
{
	struct pdu *request;
	struct iscsi_bhs_text_request *bhstr;

	request = pdu_new(conn);
	bhstr = (struct iscsi_bhs_text_request *)request->pdu_bhs;
	bhstr->bhstr_opcode = ISCSI_BHS_OPCODE_TEXT_REQUEST |
	    ISCSI_BHS_OPCODE_IMMEDIATE;
	bhstr->bhstr_flags = BHSTR_FLAGS_FINAL;
	bhstr->bhstr_initiator_task_tag = 0;
	bhstr->bhstr_target_transfer_tag = 0xffffffff;

	bhstr->bhstr_initiator_task_tag = 0; /* XXX */
	bhstr->bhstr_cmdsn = 0; /* XXX */
	bhstr->bhstr_expstatsn = htonl(conn->conn_statsn + 1);

	return (request);
}