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
struct snmp_mapping {int dummy; } ;

/* Variables and functions */
 struct snmp_oid2str* SLIST_FIRST (struct snmp_mapping*) ; 
 int /*<<< orphan*/  SLIST_INIT (struct snmp_mapping*) ; 
 int /*<<< orphan*/  SLIST_REMOVE_HEAD (struct snmp_mapping*,int /*<<< orphan*/ ) ; 
 scalar_t__ SNMP_TC_OWN ; 
 int /*<<< orphan*/  enum_pairs_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct snmp_oid2str*) ; 
 int /*<<< orphan*/  link ; 

__attribute__((used)) static void
snmp_mapping_listfree(struct snmp_mapping *headp)
{
	struct snmp_oid2str *p;

	while ((p = SLIST_FIRST(headp)) != NULL) {
		SLIST_REMOVE_HEAD(headp, link);

		if (p->string)
			free(p->string);

		if (p->tc == SNMP_TC_OWN)
			enum_pairs_free(p->snmp_enum);
		free(p);
	}

	SLIST_INIT(headp);
}