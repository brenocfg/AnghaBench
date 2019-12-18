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
struct TYPE_2__ {int /*<<< orphan*/  counter64; int /*<<< orphan*/  uint32; int /*<<< orphan*/  integer; } ;
struct snmp_value {int syntax; TYPE_1__ v; } ;
typedef  int int32_t ;

/* Variables and functions */
#define  SNMP_SYNTAX_COUNTER 135 
#define  SNMP_SYNTAX_COUNTER64 134 
#define  SNMP_SYNTAX_GAUGE 133 
#define  SNMP_SYNTAX_INTEGER 132 
#define  SNMP_SYNTAX_IPADDRESS 131 
#define  SNMP_SYNTAX_OCTETSTRING 130 
#define  SNMP_SYNTAX_OID 129 
#define  SNMP_SYNTAX_TIMETICKS 128 
 int /*<<< orphan*/  add_ip_syntax (struct snmp_value*,struct snmp_value*) ; 
 int /*<<< orphan*/  add_octstring_syntax (struct snmp_value*,struct snmp_value*) ; 
 int /*<<< orphan*/  add_oid_syntax (struct snmp_value*,struct snmp_value*) ; 
 int /*<<< orphan*/  warnx (char*,int) ; 

__attribute__((used)) static int32_t
snmpset_add_value(struct snmp_value *dst, struct snmp_value *src)
{
	if (dst == NULL || src == NULL)
		return (-1);

	switch (src->syntax) {
		case SNMP_SYNTAX_INTEGER:
			dst->v.integer = src->v.integer;
			dst->syntax = SNMP_SYNTAX_INTEGER;
			break;
		case SNMP_SYNTAX_TIMETICKS:
			dst->v.uint32 = src->v.uint32;
			dst->syntax = SNMP_SYNTAX_TIMETICKS;
			break;
		case SNMP_SYNTAX_GAUGE:
			dst->v.uint32 = src->v.uint32;
			dst->syntax = SNMP_SYNTAX_GAUGE;
			break;
		case SNMP_SYNTAX_COUNTER:
			dst->v.uint32 = src->v.uint32;
			dst->syntax = SNMP_SYNTAX_COUNTER;
			break;
		case SNMP_SYNTAX_COUNTER64:
			dst->v.counter64 = src->v.counter64;
			dst->syntax = SNMP_SYNTAX_COUNTER64;
			break;
		case SNMP_SYNTAX_IPADDRESS:
			add_ip_syntax(dst, src);
			break;
		case SNMP_SYNTAX_OCTETSTRING:
			add_octstring_syntax(dst, src);
			break;
		case SNMP_SYNTAX_OID:
			add_oid_syntax(dst, src);
			break;
		default:
			warnx("Unknown syntax %d", src->syntax);
			return (-1);
	}

	return (0);
}