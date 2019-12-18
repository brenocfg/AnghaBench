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
struct TYPE_3__ {int /*<<< orphan*/  oid; } ;
struct snmp_value {TYPE_1__ v; } ;
struct snmp_toolinfo {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  var; } ;
struct snmp_object {TYPE_2__ val; } ;
typedef  int int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  memset (struct snmp_object*,int /*<<< orphan*/ ,int) ; 
 int parse_oid_numeric (struct snmp_value*,char*) ; 
 scalar_t__ snmp_lookup_enumoid (struct snmp_toolinfo*,struct snmp_object*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int32_t
parse_oid_string(struct snmp_toolinfo *snmptoolctx,
    struct snmp_value *value, char *string)
{
	struct snmp_object obj;

	if (isdigit(string[0]))
		return (parse_oid_numeric(value, string));

	memset(&obj, 0, sizeof(struct snmp_object));
	if (snmp_lookup_enumoid(snmptoolctx, &obj, string) < 0) {
		warnx("Unknown OID enum string - %s", string);
		return (-1);
	}

	asn_append_oid(&(value->v.oid), &(obj.val.var));
	return (1);
}