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
typedef  size_t int32_t ;
struct TYPE_3__ {int /*<<< orphan*/  var; } ;

/* Variables and functions */
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
snmptool_add_vbind(struct snmp_pdu *pdu, struct snmp_object *obj)
{
	if (obj->error > 0)
		return (0);

	asn_append_oid(&(pdu->bindings[pdu->nbindings].var), &(obj->val.var));
	pdu->nbindings++;

	return (pdu->nbindings);
}