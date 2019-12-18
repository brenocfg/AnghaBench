#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct snmp_toolinfo {int dummy; } ;
struct TYPE_10__ {int syntax; } ;
struct snmp_object {TYPE_2__ val; TYPE_1__* info; } ;
typedef  int int32_t ;
typedef  enum snmp_syntax { ____Placeholder_snmp_syntax } snmp_syntax ;
struct TYPE_9__ {int /*<<< orphan*/  tc; } ;

/* Variables and functions */
 scalar_t__ GET_OUTPUT (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  ISSET_ERRIGNORE (struct snmp_toolinfo*) ; 
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
 int parse_counter (TYPE_2__*,char*) ; 
 int parse_gauge (TYPE_2__*,char*) ; 
 int parse_int_string (struct snmp_object*,char*) ; 
 int parse_ip (TYPE_2__*,char*) ; 
 int parse_oid_string (struct snmp_toolinfo*,TYPE_2__*,char*) ; 
 int parse_syntax (char*) ; 
 int parse_ticks (TYPE_2__*,char*) ; 
 int parse_uint64 (TYPE_2__*,char*) ; 
 int snmp_tc2oct (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  warnx (char*,char*) ; 

__attribute__((used)) static int32_t
parse_syntax_strval(struct snmp_toolinfo *snmptoolctx,
    struct snmp_object *object, char *str)
{
	uint32_t len;
	enum snmp_syntax syn;

	/*
	 * Syntax string here not required  - still may be present.
	 */

	if (GET_OUTPUT(snmptoolctx) == OUTPUT_VERBOSE) {
		for (len = 0 ; *(str + len) != ':'; len++) {
			if (*(str + len) == '\0') {
				warnx("Syntax missing in value - %s", str);
				return (-1);
			}
		}
		if ((syn = parse_syntax(str)) <= SNMP_SYNTAX_NULL) {
			warnx("Unknown syntax in - %s", str);
			return (-1);
		}
		if (syn != object->val.syntax) {
			if (!ISSET_ERRIGNORE(snmptoolctx)) {
				warnx("Bad syntax in - %s", str);
				return (-1);
			} else
				object->val.syntax = syn;
		}
		len++;
	} else
		len = 0;

	switch (object->val.syntax) {
		case SNMP_SYNTAX_INTEGER:
			return (parse_int_string(object, str + len));
		case SNMP_SYNTAX_IPADDRESS:
			return (parse_ip(&(object->val), str + len));
		case SNMP_SYNTAX_COUNTER:
			return (parse_counter(&(object->val), str + len));
		case SNMP_SYNTAX_GAUGE:
			return (parse_gauge(&(object->val), str + len));
		case SNMP_SYNTAX_TIMETICKS:
			return (parse_ticks(&(object->val), str + len));
		case SNMP_SYNTAX_COUNTER64:
			return (parse_uint64(&(object->val), str + len));
		case SNMP_SYNTAX_OCTETSTRING:
			return (snmp_tc2oct(object->info->tc, &(object->val),
			    str + len));
		case SNMP_SYNTAX_OID:
			return (parse_oid_string(snmptoolctx, &(object->val),
			    str + len));
		default:
			/* NOTREACHED */
			break;
	}

	return (-1);
}