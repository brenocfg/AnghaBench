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
struct snmp_oid2str {TYPE_1__* table_idx; int /*<<< orphan*/  snmp_enum; int /*<<< orphan*/  strlen; int /*<<< orphan*/  access; int /*<<< orphan*/  syntax; int /*<<< orphan*/  string; int /*<<< orphan*/  var; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_2__ {char* string; } ;

/* Variables and functions */
 int ASN_OIDSTRLEN ; 
 int /*<<< orphan*/  DEBUG (int /*<<< orphan*/ ,char*,char*,...) ; 
 int /*<<< orphan*/  asn_oid2str_r (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snmp_dump_enumpairs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

void
snmp_dump_oid2str(struct snmp_oid2str *entry)
{
	char buf[ASN_OIDSTRLEN];

	if (entry != NULL) {
		memset(buf, 0, sizeof(buf));
		asn_oid2str_r(&(entry->var), buf);
		DEBUG(stderr, "%s - %s - %d - %d - %d", buf, entry->string,
		    entry->syntax, entry->access, entry->strlen);
		snmp_dump_enumpairs(entry->snmp_enum);
		DEBUG(stderr,"%s \n", (entry->table_idx == NULL)?"No table":
		    entry->table_idx->string);
	}
}