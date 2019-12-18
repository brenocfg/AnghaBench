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
struct snmp_toolinfo {int /*<<< orphan*/  snmp_tablelist; int /*<<< orphan*/  snmp_enumlist; int /*<<< orphan*/  snmp_cnt64list; int /*<<< orphan*/  snmp_gaugelist; int /*<<< orphan*/  snmp_cntlist; int /*<<< orphan*/  snmp_ticklist; int /*<<< orphan*/  snmp_iplist; int /*<<< orphan*/  snmp_oidlist; int /*<<< orphan*/  snmp_octlist; int /*<<< orphan*/  snmp_intlist; int /*<<< orphan*/  snmp_nodelist; int /*<<< orphan*/ * mappings; } ;

/* Variables and functions */
 int /*<<< orphan*/  _bsnmptools_debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  snmp_mapping_dumplist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snmp_mapping_dumptable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

void
snmp_mapping_dump(struct snmp_toolinfo *snmptoolctx /* int bits */)
{
	if (!_bsnmptools_debug)
		return;

	if (snmptoolctx == NULL) {
		fprintf(stderr,"No snmptool context!\n");
		return;
	}

	if (snmptoolctx->mappings == NULL) {
		fprintf(stderr,"No mappings!\n");
		return;
	}

	fprintf(stderr,"snmp_nodelist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_nodelist);

	fprintf(stderr,"snmp_intlist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_intlist);

	fprintf(stderr,"snmp_octlist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_octlist);

	fprintf(stderr,"snmp_oidlist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_oidlist);

	fprintf(stderr,"snmp_iplist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_iplist);

	fprintf(stderr,"snmp_ticklist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_ticklist);

	fprintf(stderr,"snmp_cntlist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_cntlist);

	fprintf(stderr,"snmp_gaugelist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_gaugelist);

	fprintf(stderr,"snmp_cnt64list:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_cnt64list);

	fprintf(stderr,"snmp_enumlist:\n");
	snmp_mapping_dumplist(&snmptoolctx->snmp_enumlist);

	fprintf(stderr,"snmp_tablelist:\n");
	snmp_mapping_dumptable(&snmptoolctx->snmp_tablelist);
}