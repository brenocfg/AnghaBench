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
struct TYPE_4__ {int /*<<< orphan*/  var; } ;
struct snmp_object {TYPE_2__* info; TYPE_1__ val; } ;
struct asn_oid {int dummy; } ;
struct TYPE_6__ {char* str; } ;
struct TYPE_5__ {char* string; } ;

/* Variables and functions */
 int ASN_OIDSTRLEN ; 
 scalar_t__ GET_OUTPUT (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  ISSET_NUMERIC (struct snmp_toolinfo*) ; 
 scalar_t__ OUTPUT_VERBOSE ; 
 size_t SNMP_SYNTAX_OID ; 
 int /*<<< orphan*/  asn_append_oid (int /*<<< orphan*/ *,struct asn_oid*) ; 
 int /*<<< orphan*/  asn_oid2str_r (struct asn_oid*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  memset (struct snmp_object*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ snmp_lookup_enumstring (struct snmp_toolinfo*,struct snmp_object*) ; 
 scalar_t__ snmp_lookup_nodestring (struct snmp_toolinfo*,struct snmp_object*) ; 
 scalar_t__ snmp_lookup_oidstring (struct snmp_toolinfo*,struct snmp_object*) ; 
 int /*<<< orphan*/  stdout ; 
 TYPE_3__* syntax_strings ; 

__attribute__((used)) static void
snmp_output_oid_value(struct snmp_toolinfo *snmptoolctx, struct asn_oid *oid)
{
	char oid_string[ASN_OIDSTRLEN];
	struct snmp_object obj;

	if (GET_OUTPUT(snmptoolctx) == OUTPUT_VERBOSE)
		fprintf(stdout, "%s : ", syntax_strings[SNMP_SYNTAX_OID].str);

	if(!ISSET_NUMERIC(snmptoolctx)) {
		memset(&obj, 0, sizeof(struct snmp_object));
		asn_append_oid(&(obj.val.var), oid);

		if (snmp_lookup_enumstring(snmptoolctx, &obj) > 0)
			fprintf(stdout, "%s" , obj.info->string);
		else if (snmp_lookup_oidstring(snmptoolctx, &obj) > 0)
			fprintf(stdout, "%s" , obj.info->string);
		else if (snmp_lookup_nodestring(snmptoolctx, &obj) > 0)
			fprintf(stdout, "%s" , obj.info->string);
		else {
			(void) asn_oid2str_r(oid, oid_string);
			fprintf(stdout, "%s", oid_string);
		}
	} else {
		(void) asn_oid2str_r(oid, oid_string);
		fprintf(stdout, "%s", oid_string);
	}
}