#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snmp_pdu {size_t nbindings; TYPE_1__* bindings; } ;
struct TYPE_4__ {int /*<<< orphan*/  var; } ;
struct snmp_object {scalar_t__ error; TYPE_2__ val; } ;
typedef  int int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 size_t SNMP_MAX_BINDINGS ; 
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ snmpset_add_value (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int32_t
snmpset_add_vbind(struct snmp_pdu *pdu, struct snmp_object *obj)
{
	if (pdu->nbindings > SNMP_MAX_BINDINGS) {
		warnx("Too many OIDs for one PDU");
		return (-1);
	}

	if (obj->error > 0)
		return (0);

	if (snmpset_add_value(&(pdu->bindings[pdu->nbindings]), &(obj->val))
	    < 0)
		return (-1);

	asn_append_oid(&(pdu->bindings[pdu->nbindings].var), &(obj->val.var));
	pdu->nbindings++;

	return (pdu->nbindings);
}