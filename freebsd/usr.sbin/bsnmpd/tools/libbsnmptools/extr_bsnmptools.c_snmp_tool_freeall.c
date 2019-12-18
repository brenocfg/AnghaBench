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
struct snmp_toolinfo {int /*<<< orphan*/ * passwd; } ;
struct TYPE_2__ {int /*<<< orphan*/ * cport; int /*<<< orphan*/ * chost; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_filelist (struct snmp_toolinfo*) ; 
 TYPE_1__ snmp_client ; 
 int /*<<< orphan*/  snmp_mapping_free (struct snmp_toolinfo*) ; 
 int /*<<< orphan*/  snmp_object_freeall (struct snmp_toolinfo*) ; 

void
snmp_tool_freeall(struct snmp_toolinfo *snmptoolctx)
{
	if (snmp_client.chost != NULL) {
		free(snmp_client.chost);
		snmp_client.chost = NULL;
	}

	if (snmp_client.cport != NULL) {
		free(snmp_client.cport);
		snmp_client.cport = NULL;
	}

	snmp_mapping_free(snmptoolctx);
	free_filelist(snmptoolctx);
	snmp_object_freeall(snmptoolctx);

	if (snmptoolctx->passwd != NULL) {
		free(snmptoolctx->passwd);
		snmptoolctx->passwd = NULL;
	}
}