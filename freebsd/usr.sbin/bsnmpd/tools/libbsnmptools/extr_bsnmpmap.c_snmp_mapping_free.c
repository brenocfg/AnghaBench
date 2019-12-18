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
struct snmp_toolinfo {int /*<<< orphan*/ * mappings; int /*<<< orphan*/  snmp_tclist; int /*<<< orphan*/  snmp_tablelist; int /*<<< orphan*/  snmp_enumlist; int /*<<< orphan*/  snmp_cnt64list; int /*<<< orphan*/  snmp_gaugelist; int /*<<< orphan*/  snmp_cntlist; int /*<<< orphan*/  snmp_ticklist; int /*<<< orphan*/  snmp_iplist; int /*<<< orphan*/  snmp_oidlist; int /*<<< orphan*/  snmp_octlist; int /*<<< orphan*/  snmp_intlist; int /*<<< orphan*/  snmp_nodelist; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_enumtc_listfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_mapping_listfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_mapping_table_listfree (int /*<<< orphan*/ *) ; 

int
snmp_mapping_free(struct snmp_toolinfo *snmptoolctx)
{
	if (snmptoolctx == NULL || snmptoolctx->mappings == NULL)
		return (-1);

	snmp_mapping_listfree(&snmptoolctx->snmp_nodelist);
	snmp_mapping_listfree(&snmptoolctx->snmp_intlist);
	snmp_mapping_listfree(&snmptoolctx->snmp_octlist);
	snmp_mapping_listfree(&snmptoolctx->snmp_oidlist);
	snmp_mapping_listfree(&snmptoolctx->snmp_iplist);
	snmp_mapping_listfree(&snmptoolctx->snmp_ticklist);
	snmp_mapping_listfree(&snmptoolctx->snmp_cntlist);
	snmp_mapping_listfree(&snmptoolctx->snmp_gaugelist);
	snmp_mapping_listfree(&snmptoolctx->snmp_cnt64list);
	snmp_mapping_listfree(&snmptoolctx->snmp_enumlist);
	snmp_mapping_table_listfree(&snmptoolctx->snmp_tablelist);
	snmp_enumtc_listfree(&snmptoolctx->snmp_tclist);
	free(snmptoolctx->mappings);

	return (0);
}