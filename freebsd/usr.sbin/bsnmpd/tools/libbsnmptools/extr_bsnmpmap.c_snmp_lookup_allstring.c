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
struct snmp_toolinfo {int /*<<< orphan*/  snmp_nodelist; int /*<<< orphan*/  snmp_enumlist; int /*<<< orphan*/  snmp_cnt64list; int /*<<< orphan*/  snmp_ticklist; int /*<<< orphan*/  snmp_gaugelist; int /*<<< orphan*/  snmp_cntlist; int /*<<< orphan*/  snmp_iplist; int /*<<< orphan*/  snmp_oidlist; int /*<<< orphan*/  snmp_octlist; int /*<<< orphan*/  snmp_intlist; int /*<<< orphan*/ * mappings; } ;
struct snmp_object {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 scalar_t__ snmp_lookup_leaf (int /*<<< orphan*/ *,struct snmp_object*) ; 
 scalar_t__ snmp_lookuplist_string (int /*<<< orphan*/ *,struct snmp_object*) ; 

int32_t
snmp_lookup_allstring(struct snmp_toolinfo *snmptoolctx, struct snmp_object *s)
{
	if (snmptoolctx == NULL || snmptoolctx->mappings == NULL)
		return (-1);

	if (snmp_lookup_leaf(&snmptoolctx->snmp_intlist, s) > 0)
		return (1);
	if (snmp_lookup_leaf(&snmptoolctx->snmp_octlist, s) > 0)
		return (1);
	if (snmp_lookup_leaf(&snmptoolctx->snmp_oidlist, s) > 0)
		return (1);
	if (snmp_lookup_leaf(&snmptoolctx->snmp_iplist, s) > 0)
		return (1);
	if (snmp_lookup_leaf(&snmptoolctx->snmp_cntlist, s) > 0)
		return (1);
	if (snmp_lookup_leaf(&snmptoolctx->snmp_gaugelist, s) > 0)
		return (1);
	if (snmp_lookup_leaf(&snmptoolctx->snmp_ticklist, s) > 0)
		return (1);
	if (snmp_lookup_leaf(&snmptoolctx->snmp_cnt64list, s) > 0)
		return (1);
	if (snmp_lookuplist_string(&snmptoolctx->snmp_enumlist, s) > 0)
		return (1);
	if (snmp_lookuplist_string(&snmptoolctx->snmp_nodelist, s) > 0)
		return (1);

	return (-1);
}