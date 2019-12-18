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
struct snmp_table_index {int dummy; } ;
struct snmp_index_entry {int /*<<< orphan*/  index_list; struct snmp_index_entry* string; } ;

/* Variables and functions */
 struct snmp_index_entry* SLIST_FIRST (struct snmp_table_index*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct snmp_table_index*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct snmp_index_entry*) ; 
 int /*<<< orphan*/  link ; 
 int /*<<< orphan*/  snmp_index_listfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
snmp_mapping_table_listfree(struct snmp_table_index *headp)
{
	struct snmp_index_entry *t;

	while ((t = SLIST_FIRST(headp)) != NULL) {
		SLIST_REMOVE_HEAD(headp, link);

		if (t->string)
			free(t->string);

		snmp_index_listfree(&(t->index_list));
		free(t);
	}
}