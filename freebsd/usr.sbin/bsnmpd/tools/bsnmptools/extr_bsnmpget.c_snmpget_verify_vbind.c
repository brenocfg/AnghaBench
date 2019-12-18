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
struct snmp_toolinfo {int dummy; } ;
struct snmp_pdu {scalar_t__ version; scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ syntax; } ;
struct snmp_object {TYPE_1__ val; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ ISSET_NUMERIC (struct snmp_toolinfo*) ; 
 scalar_t__ SNMP_PDU_GET ; 
 scalar_t__ SNMP_PDU_GETBULK ; 
 scalar_t__ SNMP_PDU_GETNEXT ; 
 scalar_t__ SNMP_SYNTAX_COUNTER64 ; 
 scalar_t__ SNMP_SYNTAX_NULL ; 
 scalar_t__ SNMP_V1 ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int32_t
snmpget_verify_vbind(struct snmp_toolinfo *snmptoolctx, struct snmp_pdu *pdu,
    struct snmp_object *obj)
{
	if (pdu->version == SNMP_V1 && obj->val.syntax ==
	    SNMP_SYNTAX_COUNTER64) {
		warnx("64-bit counters are not supported in SNMPv1 PDU");
		return (-1);
	}

	if (ISSET_NUMERIC(snmptoolctx) || pdu->type == SNMP_PDU_GETNEXT ||
	    pdu->type == SNMP_PDU_GETBULK)
		return (1);

	if (pdu->type == SNMP_PDU_GET && obj->val.syntax == SNMP_SYNTAX_NULL) {
		warnx("Only leaf object values can be added to GET PDU");
		return (-1);
	}

	return (1);
}