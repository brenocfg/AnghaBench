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
struct snmp_toolinfo {int /*<<< orphan*/  snmp_tablelist; int /*<<< orphan*/  snmp_nodelist; int /*<<< orphan*/  snmp_cnt64list; int /*<<< orphan*/  snmp_gaugelist; int /*<<< orphan*/  snmp_cntlist; int /*<<< orphan*/  snmp_ticklist; int /*<<< orphan*/  snmp_iplist; int /*<<< orphan*/  snmp_oidlist; int /*<<< orphan*/  snmp_octlist; int /*<<< orphan*/  snmp_intlist; } ;
struct snmp_object {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ snmp_lookup_oidlist (int /*<<< orphan*/ *,struct snmp_object*,char*) ; 
 scalar_t__ snmp_lookup_tablelist (struct snmp_toolinfo*,int /*<<< orphan*/ *,struct snmp_object*,char*) ; 

int32_t
snmp_lookup_oidall(struct snmp_toolinfo *snmptoolctx, struct snmp_object *s,
    char *oid)
{
	if (snmptoolctx == NULL || s == NULL || oid == NULL)
		return (-1);

	if (snmp_lookup_oidlist(&snmptoolctx->snmp_intlist, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_octlist, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_oidlist, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_iplist, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_ticklist, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_cntlist, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_gaugelist, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_cnt64list, s, oid) > 0)
		return (1);
	if (snmp_lookup_oidlist(&snmptoolctx->snmp_nodelist, s, oid) > 0)
		return (1);
	if (snmp_lookup_tablelist(snmptoolctx, &snmptoolctx->snmp_tablelist,
	    s, oid) > 0)
		return (1);

	return (-1);
}