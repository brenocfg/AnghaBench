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
struct TYPE_3__ {int /*<<< orphan*/  octets; int /*<<< orphan*/  len; } ;
struct TYPE_4__ {int /*<<< orphan*/  counter64; int /*<<< orphan*/  uint32; int /*<<< orphan*/  ipaddress; int /*<<< orphan*/  oid; TYPE_1__ octetstring; int /*<<< orphan*/  integer; } ;
struct snmp_value {int syntax; TYPE_2__ v; } ;
struct snmp_toolinfo {int dummy; } ;
struct snmp_oid2str {int /*<<< orphan*/  tc; int /*<<< orphan*/ * snmp_enum; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ GET_OUTPUT (struct snmp_toolinfo*) ; 
 scalar_t__ OUTPUT_QUIET ; 
 int /*<<< orphan*/  SNMP_STRING ; 
#define  SNMP_SYNTAX_COUNTER 139 
#define  SNMP_SYNTAX_COUNTER64 138 
#define  SNMP_SYNTAX_ENDOFMIBVIEW 137 
#define  SNMP_SYNTAX_GAUGE 136 
#define  SNMP_SYNTAX_INTEGER 135 
#define  SNMP_SYNTAX_IPADDRESS 134 
#define  SNMP_SYNTAX_NOSUCHINSTANCE 133 
#define  SNMP_SYNTAX_NOSUCHOBJECT 132 
#define  SNMP_SYNTAX_NULL 131 
#define  SNMP_SYNTAX_OCTETSTRING 130 
#define  SNMP_SYNTAX_OID 129 
#define  SNMP_SYNTAX_TIMETICKS 128 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snmp_output_counter (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_counter64 (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_gauge (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_int (struct snmp_toolinfo*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_ipaddress (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_octetstring (struct snmp_toolinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snmp_output_oid_value (struct snmp_toolinfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_output_ticks (struct snmp_toolinfo*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

int32_t
snmp_output_numval(struct snmp_toolinfo *snmptoolctx, struct snmp_value *val,
    struct snmp_oid2str *entry)
{
	if (val == NULL)
		return (-1);

	if (GET_OUTPUT(snmptoolctx) != OUTPUT_QUIET)
		fprintf(stdout, " = ");

	switch (val->syntax) {
	    case SNMP_SYNTAX_INTEGER:
		if (entry != NULL)
			snmp_output_int(snmptoolctx, entry->snmp_enum,
			    val->v.integer);
		else
			snmp_output_int(snmptoolctx, NULL, val->v.integer);
		break;

	    case SNMP_SYNTAX_OCTETSTRING:
		if (entry != NULL)
			snmp_output_octetstring(snmptoolctx, entry->tc,
			    val->v.octetstring.len, val->v.octetstring.octets);
		else
			snmp_output_octetstring(snmptoolctx, SNMP_STRING,
			    val->v.octetstring.len, val->v.octetstring.octets);
		break;

	    case SNMP_SYNTAX_OID:
		snmp_output_oid_value(snmptoolctx, &(val->v.oid));
		break;

	    case SNMP_SYNTAX_IPADDRESS:
		snmp_output_ipaddress(snmptoolctx, val->v.ipaddress);
		break;

	    case SNMP_SYNTAX_COUNTER:
		snmp_output_counter(snmptoolctx, val->v.uint32);
		break;

	    case SNMP_SYNTAX_GAUGE:
		snmp_output_gauge(snmptoolctx, val->v.uint32);
		break;

	    case SNMP_SYNTAX_TIMETICKS:
		snmp_output_ticks(snmptoolctx, val->v.uint32);
		break;

	    case SNMP_SYNTAX_COUNTER64:
		snmp_output_counter64(snmptoolctx, val->v.counter64);
		break;

	    case SNMP_SYNTAX_NOSUCHOBJECT:
		fprintf(stdout, "No Such Object\n");
		return (val->syntax);

	    case SNMP_SYNTAX_NOSUCHINSTANCE:
		fprintf(stdout, "No Such Instance\n");
		return (val->syntax);

	    case SNMP_SYNTAX_ENDOFMIBVIEW:
		fprintf(stdout, "End of Mib View\n");
		return (val->syntax);

	    case SNMP_SYNTAX_NULL:
		/* NOTREACHED */
		fprintf(stdout, "agent returned NULL Syntax\n");
		return (val->syntax);

	    default:
		/* NOTREACHED - If here - then all went completely wrong. */
		fprintf(stdout, "agent returned unknown syntax\n");
		return (-1);
	}

	fprintf(stdout, "\n");

	return (0);
}