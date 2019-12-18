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
struct TYPE_2__ {int /*<<< orphan*/  var; } ;
struct snmp_object {TYPE_1__ val; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ ISSET_NUMERIC (struct snmp_toolinfo*) ; 
 scalar_t__ snmp_parse_numoid (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * snmptools_parse_stroid (struct snmp_toolinfo*,struct snmp_object*,char*) ; 

__attribute__((used)) static int32_t
snmptools_parse_oid(struct snmp_toolinfo *snmptoolctx,
    struct snmp_object *obj, char *argv)
{
	if (argv == NULL)
		return (-1);

	if (ISSET_NUMERIC(snmptoolctx)) {
		if (snmp_parse_numoid(argv, &(obj->val.var)) < 0)
			return (-1);
	} else {
		if (snmptools_parse_stroid(snmptoolctx, obj, argv) == NULL &&
		    snmp_parse_numoid(argv, &(obj->val.var)) < 0)
			return (-1);
	}

	return (1);
}