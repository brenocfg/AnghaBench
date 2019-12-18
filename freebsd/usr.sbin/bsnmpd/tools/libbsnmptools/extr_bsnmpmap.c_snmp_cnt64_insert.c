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
struct snmp_toolinfo {int /*<<< orphan*/  snmp_cnt64list; scalar_t__ mappings; } ;
struct snmp_oid2str {int dummy; } ;
typedef  int int32_t ;

/* Variables and functions */
 int snmp_mapping_insert (int /*<<< orphan*/ *,struct snmp_oid2str*) ; 

__attribute__((used)) static int32_t
snmp_cnt64_insert(struct snmp_toolinfo *snmptoolctx, struct snmp_oid2str *entry)
{
	if (snmptoolctx != NULL && snmptoolctx->mappings)
		return (snmp_mapping_insert(&snmptoolctx->snmp_cnt64list,entry));

	return (-1);
}