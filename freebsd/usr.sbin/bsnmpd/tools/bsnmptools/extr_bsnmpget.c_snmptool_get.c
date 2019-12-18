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
struct snmp_toolinfo {int dummy; } ;
struct snmp_pdu {int error_index; int /*<<< orphan*/  error_status; int /*<<< orphan*/ * bindings; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MAXREP (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  GET_NONREP (struct snmp_toolinfo*) ; 
 scalar_t__ GET_PDUTYPE (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  ISSET_RETRY (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  SNMP_MAX_BINDINGS ; 
 scalar_t__ SNMP_PDU_GETBULK ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int snmp_dialog (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_object_seterror (struct snmp_toolinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_err_resp (struct snmp_toolinfo*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmp_output_resp (struct snmp_toolinfo*,struct snmp_pdu*,int /*<<< orphan*/ *) ; 
 scalar_t__ snmp_parse_resp (struct snmp_pdu*,struct snmp_pdu*) ; 
 scalar_t__ snmp_pdu_add_bindings (struct snmp_toolinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct snmp_pdu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_pdu_create (struct snmp_pdu*,scalar_t__) ; 
 int /*<<< orphan*/  snmp_pdu_free (struct snmp_pdu*) ; 
 int /*<<< orphan*/  snmpget_fix_getbulk (struct snmp_pdu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmpget_verify_vbind ; 
 int /*<<< orphan*/  snmptool_add_vbind ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
snmptool_get(struct snmp_toolinfo *snmptoolctx)
{
	struct snmp_pdu req, resp;

	snmp_pdu_create(&req, GET_PDUTYPE(snmptoolctx));

	while ((snmp_pdu_add_bindings(snmptoolctx, snmpget_verify_vbind,
	     snmptool_add_vbind, &req, SNMP_MAX_BINDINGS)) > 0) {

		if (GET_PDUTYPE(snmptoolctx) == SNMP_PDU_GETBULK)
			snmpget_fix_getbulk(&req, GET_MAXREP(snmptoolctx),
			    GET_NONREP(snmptoolctx));

		if (snmp_dialog(&req, &resp) == -1) {
			warn("Snmp dialog");
			break;
		}

		if (snmp_parse_resp(&resp, &req) >= 0) {
			snmp_output_resp(snmptoolctx, &resp, NULL);
			snmp_pdu_free(&resp);
			break;
		}

		snmp_output_err_resp(snmptoolctx, &resp);
		if (GET_PDUTYPE(snmptoolctx) == SNMP_PDU_GETBULK ||
		    !ISSET_RETRY(snmptoolctx)) {
			snmp_pdu_free(&resp);
			break;
		}

		/*
		 * Loop through the object list and set object->error to the
		 * varbinding that caused the error.
		 */
		if (snmp_object_seterror(snmptoolctx,
		    &(resp.bindings[resp.error_index - 1]),
		    resp.error_status) <= 0) {
			snmp_pdu_free(&resp);
			break;
		}

		fprintf(stderr, "Retrying...\n");
		snmp_pdu_free(&resp);
		snmp_pdu_create(&req, GET_PDUTYPE(snmptoolctx));
	}

	snmp_pdu_free(&req);

	return (0);
}