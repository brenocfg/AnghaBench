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
typedef  int /*<<< orphan*/  uint32_t ;
struct snmp_pdu {int nbindings; TYPE_1__* bindings; } ;
struct asn_oid {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,struct asn_oid*) ; 
 int /*<<< orphan*/  snmp_pdu_create (struct snmp_pdu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
snmpwalk_nextpdu_create(uint32_t op, struct asn_oid *var, struct snmp_pdu *pdu)
{
	snmp_pdu_create(pdu, op);
	asn_append_oid(&(pdu->bindings[0].var), var);
	pdu->nbindings = 1;
}