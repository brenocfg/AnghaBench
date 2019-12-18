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
struct snmp_value {scalar_t__ syntax; int /*<<< orphan*/  var; } ;
struct snmp_toolinfo {int dummy; } ;
struct TYPE_2__ {scalar_t__ syntax; int /*<<< orphan*/  var; } ;
struct snmp_object {TYPE_1__ val; } ;
typedef  int int32_t ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASN_MAXID ; 
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct snmp_object*,int /*<<< orphan*/ ,int) ; 
 int snmp_lookup_leafstring (struct snmp_toolinfo*,struct snmp_object*) ; 
 int snmp_lookup_nonleaf_string (struct snmp_toolinfo*,struct snmp_object*) ; 
 int /*<<< orphan*/  snmp_suboid_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_suboid_pop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int32_t
snmp_fill_object(struct snmp_toolinfo *snmptoolctx, struct snmp_object *obj,
    struct snmp_value *val)
{
	int32_t rc;
	asn_subid_t suboid;

	if (obj == NULL || val == NULL)
		return (-1);

	if ((suboid = snmp_suboid_pop(&(val->var))) > ASN_MAXID)
		return (-1);

	memset(obj, 0, sizeof(struct snmp_object));
	asn_append_oid(&(obj->val.var), &(val->var));
	obj->val.syntax = val->syntax;

	if (obj->val.syntax > 0)
		rc = snmp_lookup_leafstring(snmptoolctx, obj);
	else
		rc = snmp_lookup_nonleaf_string(snmptoolctx, obj);

	(void) snmp_suboid_append(&(val->var), suboid);
	(void) snmp_suboid_append(&(obj->val.var), suboid);

	return (rc);
}