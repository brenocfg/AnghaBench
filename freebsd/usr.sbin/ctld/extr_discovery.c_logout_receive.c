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
struct pdu {TYPE_1__* pdu_bhs; } ;
struct iscsi_bhs_logout_request {int bhslr_reason; int bhslr_opcode; int /*<<< orphan*/  bhslr_cmdsn; int /*<<< orphan*/  bhslr_expstatsn; } ;
struct connection {int /*<<< orphan*/  conn_cmdsn; int /*<<< orphan*/  conn_statsn; } ;
struct TYPE_2__ {int bhs_opcode; } ;

/* Variables and functions */
 int BHSLR_REASON_CLOSE_SESSION ; 
 int ISCSI_BHS_OPCODE_IMMEDIATE ; 
 int ISCSI_BHS_OPCODE_LOGOUT_REQUEST ; 
 scalar_t__ ISCSI_SNLT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debugx (char*,int) ; 
 int /*<<< orphan*/  log_errx (int,char*,int,...) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 struct pdu* pdu_new (struct connection*) ; 
 int /*<<< orphan*/  pdu_receive (struct pdu*) ; 

__attribute__((used)) static struct pdu *
logout_receive(struct connection *conn)
{
	struct pdu *request;
	struct iscsi_bhs_logout_request *bhslr;

	request = pdu_new(conn);
	pdu_receive(request);
	if ((request->pdu_bhs->bhs_opcode & ~ISCSI_BHS_OPCODE_IMMEDIATE) !=
	    ISCSI_BHS_OPCODE_LOGOUT_REQUEST)
		log_errx(1, "protocol error: received invalid opcode 0x%x",
		    request->pdu_bhs->bhs_opcode);
	bhslr = (struct iscsi_bhs_logout_request *)request->pdu_bhs;
	if ((bhslr->bhslr_reason & 0x7f) != BHSLR_REASON_CLOSE_SESSION)
		log_debugx("received Logout PDU with invalid reason 0x%x; "
		    "continuing anyway", bhslr->bhslr_reason & 0x7f);
	if (ISCSI_SNLT(ntohl(bhslr->bhslr_cmdsn), conn->conn_cmdsn)) {
		log_errx(1, "received Logout PDU with decreasing CmdSN: "
		    "was %u, is %u", conn->conn_cmdsn,
		    ntohl(bhslr->bhslr_cmdsn));
	}
	if (ntohl(bhslr->bhslr_expstatsn) != conn->conn_statsn) {
		log_errx(1, "received Logout PDU with wrong ExpStatSN: "
		    "is %u, should be %u", ntohl(bhslr->bhslr_expstatsn),
		    conn->conn_statsn);
	}
	conn->conn_cmdsn = ntohl(bhslr->bhslr_cmdsn);
	if ((bhslr->bhslr_opcode & ISCSI_BHS_OPCODE_IMMEDIATE) == 0)
		conn->conn_cmdsn++;

	return (request);
}