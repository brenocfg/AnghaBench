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
struct index {int syntax; int /*<<< orphan*/  tc; } ;
typedef  int int32_t ;
typedef  enum snmp_syntax { ____Placeholder_snmp_syntax } snmp_syntax ;

/* Variables and functions */
 scalar_t__ GET_OUTPUT (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  ISSET_ERRIGNORE (struct snmp_toolinfo*) ; 
 int MAX_CMD_SYNTAX_LEN ; 
 scalar_t__ OUTPUT_VERBOSE ; 
#define  SNMP_SYNTAX_COUNTER 135 
#define  SNMP_SYNTAX_COUNTER64 134 
#define  SNMP_SYNTAX_GAUGE 133 
#define  SNMP_SYNTAX_INTEGER 132 
#define  SNMP_SYNTAX_IPADDRESS 131 
 int SNMP_SYNTAX_NULL ; 
#define  SNMP_SYNTAX_OCTETSTRING 130 
#define  SNMP_SYNTAX_OID 129 
#define  SNMP_SYNTAX_TIMETICKS 128 
 int parse_syntax (char*) ; 
 char* snmp_cnt64_2asn_oid (char*,int /*<<< orphan*/ *) ; 
 char* snmp_int2asn_oid (char*,int /*<<< orphan*/ *) ; 
 char* snmp_ip2asn_oid (char*,int /*<<< orphan*/ *) ; 
 char* snmp_oid2asn_oid (struct snmp_toolinfo*,char*,int /*<<< orphan*/ *) ; 
 char* snmp_tc2oid (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* snmp_uint2asn_oid (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  warnx (char*,...) ; 

__attribute__((used)) static char *
snmp_parse_subindex(struct snmp_toolinfo *snmptoolctx, char *str,
    struct index *idx, struct snmp_object *object)
{
	char *ptr;
	int32_t i;
	enum snmp_syntax stx;
	char syntax[MAX_CMD_SYNTAX_LEN];

	ptr = str;
	if (GET_OUTPUT(snmptoolctx) == OUTPUT_VERBOSE) {
		for (i = 0; i < MAX_CMD_SYNTAX_LEN ; i++) {
			if (*(ptr + i) == ':')
				break;
		}

		if (i >= MAX_CMD_SYNTAX_LEN) {
			warnx("Unknown syntax in OID - %s", str);
			return (NULL);
		}
		/* Expect a syntax string here. */
		if ((stx = parse_syntax(str)) <= SNMP_SYNTAX_NULL) {
			warnx("Invalid  syntax - %s",syntax);
			return (NULL);
		}

		if (stx != idx->syntax && !ISSET_ERRIGNORE(snmptoolctx)) {
			warnx("Syntax mismatch - %d expected, %d given",
			    idx->syntax, stx);
			return (NULL);
		}
		/*
		 * That is where the suboid started + the syntax length + one
		 * character for ':'.
		 */
		ptr = str + i + 1;
	} else
		stx = idx->syntax;

	switch (stx) {
		case SNMP_SYNTAX_INTEGER:
			return (snmp_int2asn_oid(ptr, &(object->val.var)));
		case SNMP_SYNTAX_OID:
			return (snmp_oid2asn_oid(snmptoolctx, ptr,
			    &(object->val.var)));
		case SNMP_SYNTAX_IPADDRESS:
			return (snmp_ip2asn_oid(ptr, &(object->val.var)));
		case SNMP_SYNTAX_COUNTER:
			/* FALLTHROUGH */
		case SNMP_SYNTAX_GAUGE:
			/* FALLTHROUGH */
		case SNMP_SYNTAX_TIMETICKS:
			return (snmp_uint2asn_oid(ptr, &(object->val.var)));
		case SNMP_SYNTAX_COUNTER64:
			return (snmp_cnt64_2asn_oid(ptr, &(object->val.var)));
		case SNMP_SYNTAX_OCTETSTRING:
			return (snmp_tc2oid(idx->tc, ptr, &(object->val.var)));
		default:
			/* NOTREACHED */
			break;
	}

	return (NULL);
}