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
struct snmp_toolinfo {int /*<<< orphan*/  snmp_tclist; int /*<<< orphan*/ * mappings; } ;
struct enum_type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct enum_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link ; 

void
snmp_enumtc_insert(struct snmp_toolinfo *snmptoolctx, struct enum_type *entry)
{
	if (snmptoolctx == NULL || snmptoolctx->mappings == NULL)
		return;	/* XXX no error handling? */

	SLIST_INSERT_HEAD(&snmptoolctx->snmp_tclist, entry, link);
}