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
struct snmp_oid2str {scalar_t__ tc; int /*<<< orphan*/  snmp_enum; struct snmp_oid2str* string; } ;

/* Variables and functions */
 scalar_t__ SNMP_TC_OWN ; 
 int /*<<< orphan*/  enum_pairs_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct snmp_oid2str*) ; 

void
snmp_mapping_entryfree(struct snmp_oid2str *entry)
{
	if (entry->string)
		free(entry->string);

	if (entry->tc == SNMP_TC_OWN)
		enum_pairs_free(entry->snmp_enum);

	free(entry);
}