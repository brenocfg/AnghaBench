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
struct snmp_pdu {scalar_t__ version; scalar_t__ error_status; scalar_t__ nbindings; int type; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ SNMP_ERR_NOERROR ; 
 scalar_t__ SNMP_ERR_NOSUCHNAME ; 
#define  SNMP_PDU_GET 130 
#define  SNMP_PDU_GETBULK 129 
#define  SNMP_PDU_GETNEXT 128 
 int snmp_parse_get_resp (struct snmp_pdu*,struct snmp_pdu*) ; 
 int snmp_parse_getbulk_resp (struct snmp_pdu*,struct snmp_pdu*) ; 
 int snmp_parse_getnext_resp (struct snmp_pdu*,struct snmp_pdu*) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

int32_t
snmp_parse_resp(struct snmp_pdu *resp, struct snmp_pdu *req)
{
	if (resp == NULL || req == NULL)
		return (-2);

	if (resp->version != req->version) {
		warnx("Response has wrong version");
		return (-1);
	}

	if (resp->error_status == SNMP_ERR_NOSUCHNAME) {
		warnx("Error - No Such Name");
		return (0);
	}

	if (resp->error_status != SNMP_ERR_NOERROR) {
		warnx("Error %d in response", resp->error_status);
		return (-1);
	}

	if (resp->nbindings != req->nbindings && req->type != SNMP_PDU_GETBULK){
		warnx("Bad number of bindings in response");
		return (-1);
	}

	switch (req->type) {
		case SNMP_PDU_GET:
			return (snmp_parse_get_resp(resp,req));
		case SNMP_PDU_GETBULK:
			return (snmp_parse_getbulk_resp(resp,req));
		case SNMP_PDU_GETNEXT:
			return (snmp_parse_getnext_resp(resp,req));
		default:
			/* NOTREACHED */
			break;
	}

	return (-2);
}