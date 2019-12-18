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
struct iscsi_bhs_login_request {int bhslr_opcode; int /*<<< orphan*/  bhslr_expstatsn; scalar_t__ bhslr_cmdsn; scalar_t__ bhslr_initiator_task_tag; int /*<<< orphan*/  bhslr_tsih; int /*<<< orphan*/  bhslr_isid; int /*<<< orphan*/  bhslr_flags; } ;
struct connection {scalar_t__ conn_statsn; int /*<<< orphan*/  conn_tsih; int /*<<< orphan*/  conn_isid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BHSLR_FLAGS_TRANSIT ; 
 int BHSLR_STAGE_FULL_FEATURE_PHASE ; 
#define  BHSLR_STAGE_OPERATIONAL_NEGOTIATION 129 
#define  BHSLR_STAGE_SECURITY_NEGOTIATION 128 
 int ISCSI_BHS_OPCODE_IMMEDIATE ; 
 int ISCSI_BHS_OPCODE_LOGIN_REQUEST ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  htonl (scalar_t__) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_errx (int,char*,int) ; 
 int /*<<< orphan*/  login_set_csg (struct pdu*,int) ; 
 int /*<<< orphan*/  login_set_nsg (struct pdu*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 struct pdu* pdu_new (struct connection*) ; 

__attribute__((used)) static struct pdu *
login_new_request(struct connection *conn, int csg)
{
	struct pdu *request;
	struct iscsi_bhs_login_request *bhslr;
	int nsg;

	request = pdu_new(conn);
	bhslr = (struct iscsi_bhs_login_request *)request->pdu_bhs;
	bhslr->bhslr_opcode = ISCSI_BHS_OPCODE_LOGIN_REQUEST |
	    ISCSI_BHS_OPCODE_IMMEDIATE;

	bhslr->bhslr_flags = BHSLR_FLAGS_TRANSIT;
	switch (csg) {
	case BHSLR_STAGE_SECURITY_NEGOTIATION:
		nsg = BHSLR_STAGE_OPERATIONAL_NEGOTIATION;
		break;
	case BHSLR_STAGE_OPERATIONAL_NEGOTIATION:
		nsg = BHSLR_STAGE_FULL_FEATURE_PHASE;
		break;
	default:
		assert(!"invalid csg");
		log_errx(1, "invalid csg %d", csg);
	}
	login_set_csg(request, csg);
	login_set_nsg(request, nsg);

	memcpy(bhslr->bhslr_isid, &conn->conn_isid, sizeof(bhslr->bhslr_isid));
	bhslr->bhslr_tsih = htons(conn->conn_tsih);
	bhslr->bhslr_initiator_task_tag = 0;
	bhslr->bhslr_cmdsn = 0;
	bhslr->bhslr_expstatsn = htonl(conn->conn_statsn + 1);

	return (request);
}