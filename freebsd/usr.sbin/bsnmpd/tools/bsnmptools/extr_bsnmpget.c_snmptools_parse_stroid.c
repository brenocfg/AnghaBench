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
struct TYPE_2__ {scalar_t__ syntax; int /*<<< orphan*/  var; } ;
struct snmp_object {TYPE_1__ val; } ;
struct asn_oid {scalar_t__ len; } ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  asn_subid_t ;

/* Variables and functions */
 scalar_t__ GET_PDUTYPE (struct snmp_toolinfo*) ; 
 int MAXSTR ; 
 scalar_t__ SNMP_PDU_GET ; 
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,struct asn_oid*) ; 
 scalar_t__ isalpha (char) ; 
 scalar_t__ isdigit (char) ; 
 int /*<<< orphan*/  memset (struct asn_oid*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snmp_lookup_oidall (struct snmp_toolinfo*,struct snmp_object*,char*) ; 
 char* snmp_parse_index (struct snmp_toolinfo*,char*,struct snmp_object*) ; 
 char* snmp_parse_suboid (char*,struct asn_oid*) ; 
 scalar_t__ snmp_suboid_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static char *
snmptools_parse_stroid(struct snmp_toolinfo *snmptoolctx,
    struct snmp_object *obj, char *argv)
{
	char string[MAXSTR], *str;
	int32_t i = 0;
	struct asn_oid in_oid;

	str = argv;

	if (*str == '.')
		str++;

	while (isalpha(*str) || *str == '_' || (i != 0 && isdigit(*str))) {
		str++;
		i++;
	}

	if (i <= 0 || i >= MAXSTR)
		return (NULL);

	memset(&in_oid, 0, sizeof(struct asn_oid));
	if ((str = snmp_parse_suboid((argv + i), &in_oid)) == NULL) {
		warnx("Invalid OID - %s", argv);
		return (NULL);
	}

	strlcpy(string, argv, i + 1);
	if (snmp_lookup_oidall(snmptoolctx, obj, string) < 0) {
		warnx("No entry for %s in mapping lists", string);
		return (NULL);
	}

	/* If OID given on command line append it. */
	if (in_oid.len > 0)
		asn_append_oid(&(obj->val.var), &in_oid);
	else if (*str == '[') {
		if ((str = snmp_parse_index(snmptoolctx, str + 1, obj)) == NULL)
			return (NULL);
	} else if (obj->val.syntax > 0 && GET_PDUTYPE(snmptoolctx) ==
	    SNMP_PDU_GET) {
		if (snmp_suboid_append(&(obj->val.var), (asn_subid_t) 0) < 0)
			return (NULL);
	}

	return (str);
}