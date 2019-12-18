#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct snmp_toolinfo {int dummy; } ;
struct snmp_pdu {int error_index; size_t error_status; TYPE_1__* bindings; scalar_t__ nbindings; } ;
struct snmp_object {int dummy; } ;
typedef  int int32_t ;
struct TYPE_6__ {char* str; } ;
struct TYPE_5__ {char* chost; char* cport; } ;
struct TYPE_4__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int ASN_OIDSTRLEN ; 
 int /*<<< orphan*/  ISSET_NUMERIC (struct snmp_toolinfo*) ; 
 size_t SNMP_ERR_INCONS_NAME ; 
 size_t SNMP_ERR_UNKNOWN ; 
 int /*<<< orphan*/  asn_oid2str_r (int /*<<< orphan*/ *,char*) ; 
 struct snmp_object* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_3__* error_strings ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (struct snmp_object*) ; 
 TYPE_2__ snmp_client ; 
 scalar_t__ snmp_fill_object (struct snmp_toolinfo*,struct snmp_object*,TYPE_1__*) ; 
 int /*<<< orphan*/  snmp_output_object (struct snmp_toolinfo*,struct snmp_object*) ; 
 int /*<<< orphan*/  stdout ; 
 char* strerror (int /*<<< orphan*/ ) ; 

void
snmp_output_err_resp(struct snmp_toolinfo *snmptoolctx, struct snmp_pdu *pdu)
{
	struct snmp_object *object;
	char buf[ASN_OIDSTRLEN];

	if (pdu == NULL || (pdu->error_index > (int32_t) pdu->nbindings)) {
		fprintf(stdout, "Invalid error index in PDU\n");
		return;
	}

	if ((object = calloc(1, sizeof(struct snmp_object))) == NULL) {
		fprintf(stdout, "calloc: %s", strerror(errno));
		return;
	}

	fprintf(stdout, "Agent %s:%s returned error \n", snmp_client.chost,
	    snmp_client.cport);

	if (!ISSET_NUMERIC(snmptoolctx) && (snmp_fill_object(snmptoolctx, object,
	    &(pdu->bindings[pdu->error_index - 1])) > 0))
		snmp_output_object(snmptoolctx, object);
	else {
		asn_oid2str_r(&(pdu->bindings[pdu->error_index - 1].var), buf);
		fprintf(stdout,"%s", buf);
	}

	fprintf(stdout," caused error - ");
	if ((pdu->error_status > 0) && (pdu->error_status <=
	    SNMP_ERR_INCONS_NAME))
		fprintf(stdout, "%s\n", error_strings[pdu->error_status].str);
	else
		fprintf(stdout,"%s\n", error_strings[SNMP_ERR_UNKNOWN].str);

	free(object);
	object = NULL;
}