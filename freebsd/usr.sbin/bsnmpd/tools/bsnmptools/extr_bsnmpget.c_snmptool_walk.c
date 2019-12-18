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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;
struct snmp_toolinfo {int dummy; } ;
struct snmp_pdu {int nbindings; TYPE_1__* bindings; } ;
struct asn_oid {int dummy; } ;
typedef  scalar_t__ int32_t ;
struct TYPE_2__ {struct asn_oid var; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MAXREP (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  GET_NONREP (struct snmp_toolinfo*) ; 
 scalar_t__ GET_PDUTYPE (struct snmp_toolinfo*) ; 
 scalar_t__ SNMP_CODE_OK ; 
 scalar_t__ SNMP_PDU_GET ; 
 scalar_t__ SNMP_PDU_GETBULK ; 
 scalar_t__ SNMP_PDU_GETNEXT ; 
 int /*<<< orphan*/  asn_append_oid (struct asn_oid*,struct asn_oid*) ; 
 int /*<<< orphan*/  memset (struct asn_oid*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snmp_dialog (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_object_remove (struct snmp_toolinfo*,struct asn_oid*) ; 
 int /*<<< orphan*/  snmp_output_err_resp (struct snmp_toolinfo*,struct snmp_pdu*) ; 
 scalar_t__ snmp_output_resp (struct snmp_toolinfo*,struct snmp_pdu*,struct asn_oid*) ; 
 scalar_t__ snmp_parse_resp (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_pdu_add_bindings (struct snmp_toolinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct snmp_pdu*,int) ; 
 int /*<<< orphan*/  snmp_pdu_create (struct snmp_pdu*,scalar_t__) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmpget_fix_getbulk (struct snmp_pdu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmptool_add_vbind ; 
 int /*<<< orphan*/  snmpwalk_nextpdu_create (scalar_t__,struct asn_oid*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  warn (char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int
snmptool_walk(struct snmp_toolinfo *snmptoolctx)
{
	struct snmp_pdu req, resp;
	struct asn_oid root;	/* Keep the initial oid. */
	int32_t outputs, rc;
	uint32_t op;

	if (GET_PDUTYPE(snmptoolctx) == SNMP_PDU_GETBULK)
		op = SNMP_PDU_GETBULK;
	else
		op = SNMP_PDU_GETNEXT;

	snmp_pdu_create(&req, op);

	while ((rc = snmp_pdu_add_bindings(snmptoolctx, NULL,
	    snmptool_add_vbind, &req, 1)) > 0) {

		/* Remember the root where the walk started from. */
		memset(&root, 0, sizeof(struct asn_oid));
		asn_append_oid(&root, &(req.bindings[0].var));

		if (op == SNMP_PDU_GETBULK)
			snmpget_fix_getbulk(&req, GET_MAXREP(snmptoolctx),
			    GET_NONREP(snmptoolctx));

		outputs = 0;
		while (snmp_dialog(&req, &resp) >= 0) {
			if ((snmp_parse_resp(&resp, &req)) < 0) {
				snmp_output_err_resp(snmptoolctx, &resp);
				snmp_pdu_free(&resp);
				outputs = -1;
				break;
			}

			rc = snmp_output_resp(snmptoolctx, &resp, &root);
			if (rc < 0) {
				snmp_pdu_free(&resp);
				outputs = -1;
				break;
			}

			outputs += rc;

			if ((u_int)rc < resp.nbindings) {
				snmp_pdu_free(&resp);
				break;
			}

			snmpwalk_nextpdu_create(op,
			    &(resp.bindings[resp.nbindings - 1].var), &req);
			if (op == SNMP_PDU_GETBULK)
				snmpget_fix_getbulk(&req, GET_MAXREP(snmptoolctx),
				    GET_NONREP(snmptoolctx));
			snmp_pdu_free(&resp);
		}

		/* Just in case our root was a leaf. */
		if (outputs == 0) {
			snmpwalk_nextpdu_create(SNMP_PDU_GET, &root, &req);
			if (snmp_dialog(&req, &resp) == SNMP_CODE_OK) {
				if (snmp_parse_resp(&resp, &req) < 0)
					snmp_output_err_resp(snmptoolctx, &resp);
				else
					snmp_output_resp(snmptoolctx, &resp,
					    NULL);
				snmp_pdu_free(&resp);
			} else
				warn("Snmp dialog");
		}

		if (snmp_object_remove(snmptoolctx, &root) < 0) {
			warnx("snmp_object_remove");
			break;
		}

		snmp_pdu_free(&req);
		snmp_pdu_create(&req, op);
	}

	snmp_pdu_free(&req);

	if (rc == 0)
		return (0);
	else
		return (1);
}