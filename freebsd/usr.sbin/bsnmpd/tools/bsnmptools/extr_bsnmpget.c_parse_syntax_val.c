#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct snmp_value {int dummy; } ;
typedef  int int32_t ;
typedef  enum snmp_syntax { ____Placeholder_snmp_syntax } snmp_syntax ;

/* Variables and functions */
 int /*<<< orphan*/  SNMP_STRING ; 
#define  SNMP_SYNTAX_COUNTER 135 
#define  SNMP_SYNTAX_COUNTER64 134 
#define  SNMP_SYNTAX_GAUGE 133 
#define  SNMP_SYNTAX_INTEGER 132 
#define  SNMP_SYNTAX_IPADDRESS 131 
#define  SNMP_SYNTAX_OCTETSTRING 130 
#define  SNMP_SYNTAX_OID 129 
#define  SNMP_SYNTAX_TIMETICKS 128 
 int parse_counter (struct snmp_value*,char*) ; 
 int parse_gauge (struct snmp_value*,char*) ; 
 int parse_int (struct snmp_value*,char*) ; 
 int parse_ip (struct snmp_value*,char*) ; 
 int parse_oid_numeric (struct snmp_value*,char*) ; 
 int parse_ticks (struct snmp_value*,char*) ; 
 int parse_uint64 (struct snmp_value*,char*) ; 
 int snmp_tc2oct (int /*<<< orphan*/ ,struct snmp_value*,char*) ; 

__attribute__((used)) static int32_t
parse_syntax_val(struct snmp_value *value, enum snmp_syntax syntax, char *val)
{
	switch (syntax) {
		case SNMP_SYNTAX_INTEGER:
			return (parse_int(value, val));
		case SNMP_SYNTAX_IPADDRESS:
			return (parse_ip(value, val));
		case SNMP_SYNTAX_COUNTER:
			return (parse_counter(value, val));
		case SNMP_SYNTAX_GAUGE:
			return (parse_gauge(value, val));
		case SNMP_SYNTAX_TIMETICKS:
			return (parse_ticks(value, val));
		case SNMP_SYNTAX_COUNTER64:
			return (parse_uint64(value, val));
		case SNMP_SYNTAX_OCTETSTRING:
			return (snmp_tc2oct(SNMP_STRING, value, val));
		case SNMP_SYNTAX_OID:
			return (parse_oid_numeric(value, val));
		default:
			/* NOTREACHED */
			break;
	}

	return (-1);
}