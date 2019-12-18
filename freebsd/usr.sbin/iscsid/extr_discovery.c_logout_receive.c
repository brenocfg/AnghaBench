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
struct iscsi_bhs_logout_response {int /*<<< orphan*/  bhslr_statsn; int /*<<< orphan*/  bhslr_response; } ;
struct connection {scalar_t__ conn_statsn; } ;
struct TYPE_2__ {scalar_t__ bhs_opcode; } ;

/* Variables and functions */
 scalar_t__ BHSLR_RESPONSE_CLOSED_SUCCESSFULLY ; 
 scalar_t__ ISCSI_BHS_OPCODE_LOGOUT_RESPONSE ; 
 int /*<<< orphan*/  log_errx (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  log_warnx (char*,scalar_t__) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 struct pdu* pdu_new (struct connection*) ; 
 int /*<<< orphan*/  pdu_receive (struct pdu*) ; 

__attribute__((used)) static struct pdu *
logout_receive(struct connection *conn)
{
	struct pdu *response;
	struct iscsi_bhs_logout_response *bhslr;

	response = pdu_new(conn);
	pdu_receive(response);
	if (response->pdu_bhs->bhs_opcode != ISCSI_BHS_OPCODE_LOGOUT_RESPONSE)
		log_errx(1, "protocol error: received invalid opcode 0x%x",
		    response->pdu_bhs->bhs_opcode);
	bhslr = (struct iscsi_bhs_logout_response *)response->pdu_bhs;
	if (ntohs(bhslr->bhslr_response) != BHSLR_RESPONSE_CLOSED_SUCCESSFULLY)
		log_warnx("received Logout Response with reason %d",
		    ntohs(bhslr->bhslr_response));
	if (ntohl(bhslr->bhslr_statsn) != conn->conn_statsn + 1) {
		log_errx(1, "received Logout PDU with wrong StatSN: "
		    "is %u, should be %u", ntohl(bhslr->bhslr_statsn),
		    conn->conn_statsn + 1);
	}
	conn->conn_statsn = ntohl(bhslr->bhslr_statsn);

	return (response);
}