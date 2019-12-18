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
struct snmp_toolinfo {int dummy; } ;
struct snmp_object {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ parse_syntax_strval (struct snmp_toolinfo*,struct snmp_object*,char*) ; 
 char* snmptools_parse_stroid (struct snmp_toolinfo*,struct snmp_object*,char*) ; 
 int /*<<< orphan*/  warnx (char*) ; 

__attribute__((used)) static int32_t
parse_pair_stroid_val(struct snmp_toolinfo *snmptoolctx,
    struct snmp_object *obj, char *argv)
{
	char *ptr;

	if ((ptr = snmptools_parse_stroid(snmptoolctx, obj, argv)) == NULL)
		return (-1);

	if (*ptr != '=') {
		warnx("Value to set expected after OID");
		return (-1);
	}

	if (parse_syntax_strval(snmptoolctx, obj, ptr + 1) < 0)
		return (-1);

	return (1);
}