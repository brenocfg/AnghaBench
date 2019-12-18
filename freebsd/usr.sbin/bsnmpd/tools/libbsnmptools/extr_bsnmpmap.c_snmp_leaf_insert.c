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
struct snmp_oid2str {int syntax; } ;
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
 int snmp_cnt64_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 
 int snmp_cnt_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 
 int snmp_gauge_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 
 int snmp_int_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 
 int snmp_ip_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 
 int snmp_oct_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 
 int snmp_oid_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 
 int snmp_tick_insert (struct snmp_toolinfo*,struct snmp_oid2str*) ; 

int32_t
snmp_leaf_insert(struct snmp_toolinfo *snmptoolctx, struct snmp_oid2str *entry)
{
	switch (entry->syntax) {
		case SNMP_SYNTAX_INTEGER:
			return (snmp_int_insert(snmptoolctx, entry));
		case SNMP_SYNTAX_OCTETSTRING:
			return (snmp_oct_insert(snmptoolctx, entry));
		case SNMP_SYNTAX_OID:
			return (snmp_oid_insert(snmptoolctx, entry));
		case SNMP_SYNTAX_IPADDRESS:
			return (snmp_ip_insert(snmptoolctx, entry));
		case SNMP_SYNTAX_COUNTER:
			return (snmp_cnt_insert(snmptoolctx, entry));
		case SNMP_SYNTAX_GAUGE:
			return (snmp_gauge_insert(snmptoolctx, entry));
		case SNMP_SYNTAX_TIMETICKS:
			return (snmp_tick_insert(snmptoolctx, entry));
		case SNMP_SYNTAX_COUNTER64:
			return (snmp_cnt64_insert(snmptoolctx, entry));
		default:
			break;
	}

	return (-1);
}